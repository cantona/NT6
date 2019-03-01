// /adm/obj/check_config.c
// by Find.

#define need(x) badness += x+"\n"

#define FOOTER "≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒\n"
#define IMPOSSIBLE_TO_MISS_HEADER \
               FOOTER \
               "『 你現在運行的 MudOS driver 的設置參數並不適合 』\n" \
               "『 此 Mudlib, 請對 driver 原碼內的 'options.h'  』\n" \
               "『 作如下的調整然後重新編譯.                    』\n" \
               FOOTER

private
void create()
{
        string badness = "";
        string version = __VERSION__;

        seteuid(getuid());
        switch (version[0..8])
        {
                case "MudOS 0.9":
                case "MudOS v20":
                case "MudOS v21":
                badness += "你的 MudOS driver 版本過時了,請使用 MudOS v22 及以後的版本.\n";
        }

#ifdef __CAST_CALL_OTHERS__
        need("需要: #undef CAST_CALL_OTHERS");
#endif

#ifdef __NO_ADD_ACTION__
        need("需要: #undef NO_ADD_ACTION");
#endif

#ifdef __NO_ENVIRONMENT__
        need("需要: #undef NO_ENVIRONMENT");
#endif

#ifdef __NO_WIZARDS__
        need(需要: "#undef NO_WIZARDS");
#endif

#ifndef __OLD_ED__
        need("需要: #define OLD_ED");
#endif
/*
#ifdef __MUDLIB_ERROR_HANDLER__
        need("需要: #undef MUDLIB_ERROR_HANDLER");
#endif
*/
#ifdef __NO_RESETS__
        need("需要: #undef NO_RESETS");
#endif

#ifdef __LAZY_RESETS__
        need("需要: #undef LAZY_RESETS");
#endif

#ifndef __TRAP_CRASHES__
        need("需要: #define TRAP_CRASHES");
#endif

#ifndef __THIS_PLAYER_IN_CALL_OUT__
        need("需要: #define THIS_PLAYER_IN_CALL_OUT");
#endif

#ifndef __CALLOUT_HANDLES__
        need("需要: #define CALLOUT_HANDLES");
#endif

#ifdef __PRIVS__
        need("需要: #undef PRIVS");
#endif

#ifndef __PACKAGE_UIDS__
        need("需要: #define PACKAGE_UIDS");
#endif

#ifndef __AUTO_SETEUID__
        need("需要: #define AUTO_SETEUID");
#endif

#ifndef __AUTO_TRUST_BACKBONE__
        need("需要: #define AUTO_TRUST_BACKBONE");
#endif

        if( strlen(badness) )
                error("\n\ndriver 配置錯誤:\n" + IMPOSSIBLE_TO_MISS_HEADER + badness + FOOTER+"\n\n");
}
