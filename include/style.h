#pragma once

namespace style {
const char* end{"\033[0;0m"};
namespace effects {
const char* bold{"\033[1m"};
const char* dull{"\033[2m"};
const char* italic{"\033[3m"};
const char* underline{"\033[4m"};
const char* inverted{"\033[7m"};
}  // namespace effects
namespace bg {
const char* dark_black{"\033[40m"};
const char* dark_red{"\033[41m"};
const char* dark_green{"\033[42m"};
const char* dark_yellow{"\033[43m"};
const char* dark_blue{"\033[44m"};
const char* dark_magenta{"\033[45m"};
const char* dark_cyan{"\033[46m"};
const char* dark_white{"\033[47m"};
const char* light_black{"\033[100m"};
const char* light_red{"\033[101m"};
const char* light_green{"\033[102m"};
const char* light_yellow{"\033[103m"};
const char* light_blue{"\033[104m"};
const char* light_magenta{"\033[105m"};
const char* light_cyan{"\033[106m"};
const char* light_white{"\033[107m"};
}  // namespace bg
namespace fg {
const char* dark_black{"\033[30m"};
const char* dark_red{"\033[31m"};
const char* dark_green{"\033[32m"};
const char* dark_yellow{"\033[33m"};
const char* dark_blue{"\033[34m"};
const char* dark_magenta{"\033[35m"};
const char* dark_cyan{"\033[36m"};
const char* dark_white{"\033[37m"};
const char* light_black{"\033[90m"};
const char* light_red{"\033[91m"};
const char* light_green{"\033[92m"};
const char* light_yellow{"\033[93m"};
const char* light_blue{"\033[94m"};
const char* light_magenta{"\033[95m"};
const char* light_cyan{"\033[96m"};
const char* light_white{"\033[97m"};
}  // namespace fg
}  // namespace style
