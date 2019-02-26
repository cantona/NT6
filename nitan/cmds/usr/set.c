// set.c
#include <ansi.h>

#define MAX_ENV_VARS        40
 
int help();

#define LIST_TERM               1
#define STRING_TERM             2
#define NUMBER_TERM             4
#define NON_ZERO                8
#define ENABLE_COLOR            16
#define NON_NEG                 0x10
#define WIZ_ONLY                0x80

mapping query_terms() { return ([
        "auto_ban"          : LIST_TERM,
        "auto_drinkout"   : 0,
        "auto_invite"          : LIST_TERM,
        "auto_regenerate" : 0,
        "auto_say"        : 0,
        "auto_war"        : 0,
        "auto_reply"      : 0,
        "reply_msg"       : 0,
        "brief"           : 0,
        "board_mode"      : 0,
        "reply_mode"      : 0,
        "combatd"         : 0,
        "combat_brief"    : 0,
        "careful"         : 0,
        "can_accept"      : LIST_TERM,
        "can_emote"       : LIST_TERM,
        "can_snoop"       : LIST_TERM,
        "can_tell"        : LIST_TERM,
        "default_sign"    : NUMBER_TERM | NON_NEG | NON_ZERO,
        "halt_age"        : 0,
        "jam_talk"        : 0,
        "keep_idle"       : 0,
        "look_window"     : 0,
        "no_accept"       : LIST_TERM,
        "no_autoultra"    : 0,
        "no_emote"        : LIST_TERM,
        "no_more"         : 0,
        "no_teach"        : 0,
        "no_tell"         : LIST_TERM,
        "no_realnews"     : 0,
        "no_story"        : 0,
        "no_task"         : 0,
        "no_follow"       : 0,
        "no_moutmsg"      : 0,
        "no_minmsg"       : 0,
        "no_dizziness"    : 0,
        "prompt"          : 0,
        "public"          : 0,
        "pure_say"        : 0,
        "invisible_item"  : 0,
        "share_exp"       : 0,
        "sign1"           : STRING_TERM,
        "sign2"           : STRING_TERM,
        "sign3"           : STRING_TERM,
        "sign4"           : STRING_TERM,
        "sign5"           : STRING_TERM,
        "show_map"        : 0,
        "wimpy"           : 0,
        "wimpy_apply"     : 0,
// wiz term
        "combat_test"     : 0,
        "invisible"       : WIZ_ONLY,
        "immortal"        : WIZ_ONLY,
        "msg_out"         : WIZ_ONLY | STRING_TERM | ENABLE_COLOR,
        "msg_in"          : WIZ_ONLY | STRING_TERM | ENABLE_COLOR,
        "no_prefix"          : WIZ_ONLY,
        "use_shell"       : WIZ_ONLY,
]); }

mapping query_env_domains() { return ([
        "combatd" : ([
                "normal" : 0,
                "damage" : 1,
                "brief"  : 2,
                "self"   : 3,
                "null"   : 4,
        ]),
        "jam_talk" : ([
                "none" : 0,
                "half" : 1,
                "abs"  : 2,
        ]),
]); }

int main(object me, string arg)
{
        int i;
        int k;
        mapping env_domains;
        string msg;

        mapping term_map;
        string *terms;
        string term;
        mixed data;
        mapping env;
        mapping d;
        string *ks;
        mixed *bs;

        int opt_add, opt_del;
 
        env=query("env", me);

        term_map = query_terms();
        env_domains = query_env_domains();
 
        if (! arg || arg == "")
        {
                msg = "你目前設定的環境變數有：\n";
                if (! mapp(env) || ! sizeof(env))
                        msg = "你目前沒有設定任何環境變數。\n";
                else
                {
                        terms = sort_array(keys(env), 1);
                        for (i = 0; i < sizeof(terms); i++)
                        {
                                if (mapp(d = env_domains[terms[i]]))
                                {
                                        ks = keys(d);
                                        for (k = 0; k < sizeof(ks); k++)
                                                if (d[ks[k]] == env[terms[i]])
                                                        break;
                                        if (k < sizeof(ks))
                                        {
                                                msg += sprintf("%-20s  %O\n",
                                                       terms[i], ks[k]);
                                                continue;
                                        }
                                }
                                msg += sprintf("%-20s  %O\n", terms[i], env[terms[i]]);
                        }
                }
                write(msg);
                return 1;
        }
 
        opt_add = 0;
        opt_del = 0;
        // mysql裏無法保存\n
        arg = replace_string(arg, "\"", "~");
        arg = replace_string(arg, "\\", "");
        if (sscanf(arg, "%s -a %s", term, data) == 2 ||
            sscanf(arg, "-a %s %s", term, data) == 2)
        {
                opt_add = 1;
        } else
        if (sscanf(arg, "%s -d %s", term, data) == 2 ||
            sscanf(arg, "-d %s %s", term, data) == 2)
        {
                opt_del = 1;
        } else
        if (sscanf(arg, "%s %s", term, data) != 2)
        {
                term = arg;
                if (term_map[term] & STRING_TERM ||
                    term_map[term] & NUMBER_TERM)
                        return notify_fail("你必須指明這個參數的內"
                                           "容，否則請用 unset 取消這個參數。\n");
                else
                        data = "YES";
        }
 
        if (data == "")
                return notify_fail("設定的參數值不能為空。\n");

        if (term_map[term] & NUMBER_TERM)
        {
                sscanf(data, "%d", data);
                if (! intp(data)) data = 0;
                if ((term_map[term] & NON_ZERO) && ! data)
                        return notify_fail("這個參數值不能設置為零。\n");

                if ((term_map[term] & NON_NEG) && data < 0)
                        return notify_fail("這個參數值不能設置為負數。\n");
        } else
        if (term_map[term] & STRING_TERM &&
            term_map[term] & ENABLE_COLOR)
        {
                data = color_filter(data);
                if (strsrch(data, ESC) != -1)
                        data += NOR;
        }

        if (term && term != "")
        {
                if (mapp(env) && undefinedp(env[term]) && sizeof(env) >= MAX_ENV_VARS)
                        return notify_fail("你設的環境變數太多了，請先用 unset 刪掉幾個吧。\n");

                if (undefinedp(term_map[term]))
                        return notify_fail("你只能設定規定的參數，請參見help settings。\n");

                if ((wiz_level(me) == 0) && (term_map[term] & WIZ_ONLY))
                        return notify_fail("只有巫師能用這個設定。\n");

                if (term_map[term] & LIST_TERM)
                {
                        if (! stringp(data) || data == "YES")
                                return notify_fail("列表參數只能以字符串為取值。\n");

                        ks = explode(data, ",") - ({ "" });
                        bs = ({ });
                        for (i = 0; i < sizeof(ks); i++)
                        {
                                if (member_array(ks[i], bs) == -1)
                                        bs += ({ ks[i] });
                        }
                        data = implode(bs, ",");
                }

                if (opt_add || opt_del)
                {
                        if (! (term_map[term] & LIST_TERM))
                                return notify_fail("這個參數不具有列表屬性，不"
                                                   "能使用-a或則是-d參數。\n");
                        if (opt_add)
                                data=add_sub(data,query("env/"+term, me));
                        else
                                data=remove_sub(data,query("env/"+term, me));
                        if (strlen(data) > 256)
                                return notify_fail("參數取值太長了。\n");

                        if (! data)
                        {
                                delete("env/"+term, me);
                                write("取消環境參數：" + term + "\n");
                                return 1;
                        }
                }

                if (mapp(d = env_domains[term]))
                {
                        if (! undefinedp(d[data])) data = d[data];

                        // check the data
                        ks = keys(d);
                        for (k = 0; k < sizeof(ks); k++)
                                if (d[ks[k]] == data) break;
                        if (k >= sizeof(ks))
                        {
                                write("該項參數不能設置成該值，請參見help settings。\n");
                                return 1;
                        }
                        set("env/"+term, data, me);
                        write(sprintf("設定環境變數：%s = %O\n", term, ks[k]));
                        return 1;
                } else
                if (stringp(data) && ! (term_map[term] & LIST_TERM) &&
                    ! (term_map[term] & STRING_TERM))
                        sscanf(data, "%d", data);

                set("env/"+term, data, me);
                write(sprintf("設定環境變數：%s = %O\n", term, data));
                return 1;
        }
        return help();
}
 
int help()
{
        write(@TEXT
指令格式：set <變數名> -a | -d [<參數>]
 
這個指令讓你設定一些環境變數，不加參數時會顯示你目前設定的環境變數，不指定
變數值，則內定值為 "YES"。如果使用了-a參數，表示將參數加入到原有的參數中，
如果使用了-d參數則表示將參數從原有的參數中去掉。只有具有多值屬性的參數才能
使用這兩個參數。

比如no_tell參數，可以設定為不收聽test和work的講話：
set no_tell test,work

如果這時候你不希望收聽nothing的講話，則可以：
set no_tell -a nothing  也可以：set no_tell test,work,nothing

如果這時候你希望收聽test的講話，則可以：
set no_tell -d test     也可以：set no_tell work,nothing

取消變數設定請用 unset 指令。

至於有哪些環境變數可以設定，請見 help settings。
TEXT
        );
        return 1;
}
