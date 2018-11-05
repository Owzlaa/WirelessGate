var fs = require('fs')
var logger = fs.createWriteStream('log.txt', {
  flags: 'a' // 'a' means appending (old data will be preserved)
})

logger.write('some data') // append string to your file
logger.write('more data') // again
logger.write('and more') // again