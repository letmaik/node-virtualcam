#include <stdexcept>
#include <nan.h>
#include "controller/controller.h"

NAN_METHOD(start) {
    int width = Nan::To<int>(info[0]).FromJust();
    int height = Nan::To<int>(info[1]).FromJust();
    double fps = Nan::To<double>(info[2]).FromJust();
    int delay = Nan::To<int>(info[3]).FromJust();
    if (!virtual_output_start(width, height, fps, delay))
        throw std::runtime_error("error starting virtual camera output");
}

NAN_METHOD(stop) {
    virtual_output_stop();
}

NAN_METHOD(send) {
    if (!virtual_output_is_running())
        return;
    int64_t timestamp = Nan::To<int64_t>(info[0]).FromJust();
    v8::Local<v8::TypedArray> ta = info[1].As<v8::TypedArray>();
    Nan::TypedArrayContents<uint8_t> frame(ta);
    uint8_t* buf = *frame;
    if (buf == nullptr)
        throw std::runtime_error("invalid frame (not a uint8 typed array)");
    int width, height;
    virtual_output_size(&width, &height);
    size_t n_lines = height;
    size_t line_size = width * 4;
    if (frame.length() != n_lines * line_size)
        throw std::runtime_error("frame has incorrect size, must be (h,w,c=4) in C memory layout");
    uint8_t** data = (uint8_t**) malloc(sizeof(uint8_t*) * n_lines);
    for (size_t i=0; i < n_lines; i++)
        data[i] = buf + i*line_size;
    virtual_video(timestamp, data);
    free(data);
}

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New<v8::String>("start").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(start)).ToLocalChecked());

  Nan::Set(target, Nan::New<v8::String>("stop").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(stop)).ToLocalChecked());

  Nan::Set(target, Nan::New<v8::String>("send").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(send)).ToLocalChecked());
}

NODE_MODULE(binding, InitAll)
