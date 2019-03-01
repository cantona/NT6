//qianyuan.c

#include <room.h>;
inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "唐門前院");
        set("long",
"來了前院，一股花香撲鼻而來，你不由的深深的吸了一口氣，好香啊\n"
"！四周都是一些花，有知名的，有不認識的，但有一朵花是最突出的，你\n"
"不禁想上去摘下來。旁邊有一個小木牌(sign)。\n"
);
        set("exits", ([
                "out"   : __DIR__"tmdamen",
                "north" : __DIR__"shuige1",
        ]));
        set("item_desc", ([
                "sign" : (HIG"路邊的野花不要採，家裡花兒也不要摘\n"NOR),
        ]));        
        set("outdoors", "tangmen");
        setup();
}

void init()
{
        add_action("do_zhai","zhai");
}

int do_zhai(string arg)
{
        object me;
      
        me = this_player();
      
        tell_object(me,HIR"你死了！\n"NOR);    
      
        return 1;
}      