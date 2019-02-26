// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit ITEM;
// 如果字符串被設置成這個值，表示輸入的字符串具有非法的格式
#define ILLEGAL_STR     "."
// 在convert時看看要不要去掉彩色
#define NOCOLOR         1
#define COLORABLE       0

int legal_chinese(string str);
string converts(string arg, int max_len, int no_color);

void create()
{
        set_name(RED "更名卷軸" NOR, ({ "idname scroll", "scroll" }) );
        set_weight(30);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "可以使自造裝備改變(idname)代號和中文名的更名卷軸。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "張");
        }

        setup();
}

void init()
{
        add_action("do_idname", "idname");
}

int do_idname(string arg)
{
        object me;
        object ob;
        string what, sname, sid, id;
        string filename, content_str;
        array content;
        int i, n;

        me = this_player();
        if (! arg || sscanf(arg, "%s %s %s", what, sname, sid) != 3)
        {
                write("格式不對！應該是：idname <物品ID> <新名字> <新ID>\n例如：idname baojian 長劍 sword\n");
                return 1;
        }

        if (! objectp(ob = present(what, me)))
                return notify_fail("你身上沒有這種東西。\n");

        if (! ob->is_item_make())
                return notify_fail("只有自造物品方可用之修改名稱或描述。\n");

        if( ob->item_owner() != query("id", me) )
                return notify_fail("這個東西的主人並不是你。\n");

        // ILLEGAL_STR = "." 表示非法的輸入
        if ((sname = converts(sname, 14, COLORABLE)) == ILLEGAL_STR)
                return 1;

        if ((sid = converts(sid, 12, NOCOLOR)) == ILLEGAL_STR)
                return 1;

        if (! sname || ! sid)
        {
                write("你好好個定個名字！\n");
                return 1;
        }

        if (! is_chinese(filter_color(sname, 1)))
        {
                write("裝備的名字必須是中文。\n");
                return 1;
        }

        if (! is_legal_id(sid))
        {
                write("英文代號必須全部用小寫英文才可以！\n");
                return 1;
        }

        if (strlen(filter_color(sname)) < 4)
        {
                write("名字至少兩個漢字！\n");
                return 1;
        }

        if (strlen(sid) < 3)
        {
                write("代號至少三個字符！\n");
                return 1;
        }

        if (sname[0] == 27 &&
            sname[4] == 'm')
        {
                // Add color prefix
                sname = NOR + sname;
        }

        filename = base_name(ob) + ".c";
        sscanf(filename, "%*s-%s.c", id);
        content_str = read_file(filename);
        destruct(ob);
        rm(filename);
        content = explode(content_str, "\n");
        n = sizeof(content);
        for (i = 0; i < n; i++)
        {
                if (strsrch(content[i], "set_name") != -1)
                        content[i] = sprintf("\tset_name(\"%s\", ({ \"%s\", \"%s\" }));",
                                             sname, sid, id);
                write_file(filename, content[i] + "\n");
        }

        write("名字：" CYN + sname + "    代號：" CYN + sid + NOR "\n");
        catch(call_other(filename, "???"));
        ob = find_object(filename);
        if (! ob)
        {
                write(HIR "修改出現問題，請彙報給巫師！\n" NOR);
        }
        else
        {
                ob->move(me, 1);
                write("修改成功，SUMMON ID不變。\n");
                destruct(this_object());
        }

        return 1;
}

// 判斷是否是合法的漢字
int legal_chinese(string str)
{
        int i;

        if (strlen(str) < 2) return 0;

        for (i = 0; i < strlen(str); i++)
        {
                if (str[i] < 161 || str[i] == 255) return 0;
                if ((! (i % 2)) && str[i] >= 248) return 0;
        }

        return 1;
}

// 轉換字符串中的顏色標誌
string converts(string arg, int max_len, int no_color)
{
        int i;

        // 去除字符串中的空格，引號，避免被別人利用做破壞
        arg = replace_string(arg, " ", "");
        arg = replace_string(arg, "\"", "'");

        for (i = 0; i < strlen(arg) - 1; i++)
        {
                if (arg[i] == '\\' && arg[i + 1] != 'n')
                {
                        write("字符'\\'後面只能跟隨n字符表示回車！\n");
                        return ILLEGAL_STR;
                }
        }

        arg = replace_string(arg, ",", "，");
        arg = replace_string(arg, ":", "：");
        arg = replace_string(arg, "?", "？");

        if (no_color)
        {
                arg = filter_color(arg, 1);
        } else
        {
                arg = trans_color(arg, 3);
                if (strlen(arg) < strlen(NOR) ||
                    arg[strlen(arg) - strlen(NOR)..<1] != NOR)
                {
                        // append NOR at tail
                        arg += NOR;
                }
        }
        if (strlen(filter_color(arg, 1)) > max_len)
        {
                write("對不起，這個字符串太長了，請不要輸入超過" + chinese_number(max_len) +
                      "個字符長的字符串。\n");
                // 表示非法的輸入
                return ILLEGAL_STR;
        }
        return arg;
}
