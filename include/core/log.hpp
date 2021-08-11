#ifndef LOG_H_
#define LOG_H_

#define LOG(msg) \
    std::cout << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl

#endif // LOG_H_
