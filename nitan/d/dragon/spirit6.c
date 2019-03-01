inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "龍潭入口");
        set("long",
"[1;32m前方就是龍潭，進去前請三思。如果到此止步，還來得及。\n"
"如要回頭，請鍵入back。在西面，有一個向下的通道，看來似乎相當深。\n"
);

        set("exits", ([ 
              "north" : __DIR__"dragoncave", 
              "westdown" : __DIR__"spirit7", 
           ]));

        set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_back", "back");
}

int do_back(object me)
{
        me=this_player();
        message_vision(HIC"$N的身影消失在一陣光芒中。\n"NOR,me); 
        set_temp("mark/diary", 0, me);
        set_temp("m_success/初級", 0, me);
        set_temp("m_success/幻影", 0, me);
        set_temp("m_success/孽龍", 0, me);
        me->move("/d/city/wumiao");
        return 1;
}
