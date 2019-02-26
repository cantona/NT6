// Code of ShenZhou
// Room: /d/mingjiao/mj_center.c
// Zhangchi 3/00

#include <ansi.h>
inherit ROOM;

int do_check();
int f_set_jingtie(string);
int f_set_didao(string);
string word_string();
string show_data();

void create()
{
        set("short", HIR"明教指揮中心"NOR);
        set("long", @LONG
這裏是明教指揮中心。四周擺滿了各種各樣的儀器。牆上面還有
一行小字(word)。正面一個一百零八寸的大屏幕(screen)上顯示着一
些數據。？
LONG );
        set("exits", ([
                "out": "/d/city/wumiao",
        ]));
        set("valid_startroom", 1);
        set("item_desc", ([
                "word": (: word_string :),
                "screen": (: show_data :),
        ]) );
        set("jingtie", 0);
        set("didao", ([
                "east":1,
                "west":0,
                "north":0,
                "south":0,
        ]));

        setup();
}

void reset()
{
        ::reset();
        // set("no_clean_up", 0);
}

void init()
{
        add_action("do_check","check_jingtie");
        add_action("f_set_jingtie","set_jingtie");
        add_action("f_set_didao","set_didao");
}

int do_check()
{
        write("現有"+query("jingtie")+"塊精鐵\n");
        return 1;
}

int f_set_jingtie(string arg)
{
        int num;

        if (arg)
        {
                if (sscanf(arg, "%d",num) != 1)
                        return notify_fail("指令格式：set_jingtie <num>\n");
        }
        else
                return notify_fail("指令格式：set_jingtie <num>\n");
        set("jingtie",num);
        write("OK!\n");
        return 1;
}

int f_set_didao(string arg)
{
        string dir;
        int num;

        if (arg)
        {
                if (sscanf(arg, "%s %d", dir, num) != 2)
                        return notify_fail("指令格式：set_didao <dir> <num>\n");
        }
        else
                return notify_fail("指令格式：set_didao <dir> <num>\n");
        set("didao/"+dir, num);
        write("OK!\n");
        return 1;
}

string word_string()
{
        return HIC
                "查精鐵儲藏量:                check_jingtie\n"+
                "設置精鐵儲藏:                set_jingtie <num>\n"+
                "設置厚土地道:                set_didao <dir> <num>\n"
                NOR
                HIR"\n\n正在建設中。\n"NOR;
}

string show_data()
{        return HIY
"\n    *-------------------------------------------*"+
        "\n\t精鐵儲藏量                "+query("jingtie")+
        "\n\t厚土地道："+
        "\n\t                東：        "+query("didao/east")+
        "\n\t                西：        "+query("didao/west")+
        "\n\t                北：        "+query("didao/north")+
        "\n\t                南：        "+query("didao/south")+
"\n    *-------------------------------------------*\n\n"+NOR;
}