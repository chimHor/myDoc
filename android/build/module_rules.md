BUILD_STATIC_LIBRARY
BUILD_SHARED_LIBRARY
BUILD_EXECUTABLE
BUILD_JAVA_LIBRARY
BUILD_STATIC_JAVA_LIBRARY
BUILD_PACKAGE
```mermaid
graph LR;
static_library.mk-->binary.mk
shared_library.mk-->dynamic_binary.mk
executable.mk-->dynamic_binary.mk
java_library.mk-->java.mk
static_java_library.mk-->java_library.mk
package.mk-->java.mk
dynamic_binary.mk-->binary.mk
binary.mk-->base_rules.mk
java.mk-->base_rules.mk
style static_library.mk fill:#00FFFF;
style shared_library.mk fill:#00FFFF;
style executable.mk fill:#00FFFF;
style java_library.mk fill:#00FFFF;
style static_java_library.mk fill:#00FFFF;
style package.mk fill:#00FFFF;
ONE_SHOT_MAKEFILE-->static_library.mk
ONE_SHOT_MAKEFILE-->shared_library.mk
ONE_SHOT_MAKEFILE-->executable.mk
ONE_SHOT_MAKEFILE-->java_library.mk
ONE_SHOT_MAKEFILE-->static_java_library.mk
ONE_SHOT_MAKEFILE-->package.mk
style ONE_SHOT_MAKEFILE fill:#00FF00;
    ```