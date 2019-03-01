// ximen.c
 

inherit ROOM;
#include <ansi.h>;

string look_gaoshi();
string get_killer();

void create()
{
        set("short", "西門");
        set("long",
"這是唐家鎮的西門，說是西門，其實就是一個崗哨，所有來往的行個\n"
"都要受到檢查。這是蜀中唐門為了安全，在這兒設了一個哨位。過往的人\n"
"不準攜帶兵器。城牆上貼著幾張通緝告示(gaoshi)。一條筆直的青石板大\n"
"道向東西兩邊延伸。再往西邊就是蜀中唐門了，東邊是鎮裡。\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 1);
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));

        set("exits", ([
                "east"  : __DIR__"xdajie",
                "northwest"  : __DIR__"ximenroad",
        ]));
        set("objects", ([
                CLASS_D("tangmen") + "/tangrou" : 1,
        ]));
        setup();
}

string look_gaoshi()
{
        return HIR"\n                              唐門通緝榜                    \n\n\n"NOR+get_killer() +HIC"\n\n                                               蜀中唐門             \n                                               唐君傷     \n"NOR;
}

string get_killer()
{
        int i;
        string msg;
        object *ob = users();

        msg = "";
        for (i = 0; i < sizeof(ob); i++)
                if( ob[i]->query_condition("killer") && query("family/family_name", ob[i]) == "唐門世家" )
                        msg += (ob[i]->short() + "\n");
        if (msg == "")
                return "沒有違規者。\n";
        else
                return "現在正在緝拿以下違規弟子：\n\n" + msg;
}
