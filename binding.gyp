{
  'targets': [
    {
      'target_name': 'binding',
      'sources': [ 'binding.cpp', 'src/controller/controller.cpp', 'src/queue/share_queue_write.cpp' ],
      'include_dirs': [
        'src',
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}