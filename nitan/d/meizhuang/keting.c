#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "迎客亭"); 
        set("long", @LONG
通過四雅清風，你來到了梅莊的迎客亭，這裏雖然只有一張石桌
(table) 和幾個石凳，但卻是一塵不染，石凳和石桌之間的空隙很大，
顯是方便來客與主人相互寒暄。
LONG );
        set("exits", ([
                "south" : __DIR__"dating",
                "north" : __DIR__"senlin1",
        ]));

        set("objects", ([
                CLASS_D("meizhuang") + "/ding" : 1,
        ]));

        set("no_clean_up", 0);

        setup();
}

void init()
{
        add_action("do_zuan", "zuan");
}

int do_zuan(string arg)
{
        object ob;
        string dir;
        object me = this_player();

        if (arg != "table")
        {
                write("你要往哪兒鑽？\n");
                return 1;
        }

        if (objectp(ob = present("shi lingwei", this_object())) &&
            living(ob))
        {
                write("你偷偷的看了看" + ob->name() + "，不敢亂來。\n");
                return 1;
        }

        write("你躡手躡腳的繞到石桌的後面，鑽進了下面的一個小洞。\n");
        if((int)me->query_skill("dodge",1) >= 30)
        {
              write("你費盡九牛二虎之力，發現自己到了一個很神祕的地道里。\n");
              me->move(__DIR__"didao1");
              return 1;
        }
        write("你試着鑽了一下後面的一個小洞，發現鑽不進去。\n");
        addn("jing", -10, me);
        addn("qi", -10, me);

        return 1;
}


int valid_leave(object me, string dir)
{
        object ding;

        if (dir != "north" ||
            ! objectp(ding = present("ding jian", this_object())))
                return ::valid_leave(me, dir);

        return ding->permit_pass(me, dir);
}