// Room: xiaoting

#include <ansi.h>
inherit ROOM;

void init();
int do_tap(string);
int do_sit(string);
void delete_served(object);

void create()
{
        set("short", "曉寒廳");
        set("long", @LONG
這是一間小廳，廳雖不大，布置倒也別致。滿廳的芳香，沁人心
脾。只見牆上掛著幾幅條幅，筆致頗為瀟洒，但掩不住幾分柔弱之氣。
廳內四周精巧地擺著些桌子(table)和椅子(chair)。
LONG );
        set("exits", ([
            "west" : __DIR__"qinyun",
            "east" : __DIR__"cuixia",
            "north" : __DIR__"xiaojing",
            "south" : __DIR__"chufang",
        ]));

        set("item_desc", ([
            "table" : "一張典雅的桃木小桌，上面放著水果盤和飲茶器具。\n",
            "chair" : "一只青竹打制的靠椅，躺上去搖搖晃晃，好舒服耶！\n",
        ]));

        set("objects",([
              __DIR__"npc/susu" : 1,
              __DIR__"obj/gao" : 2,
              __DIR__"obj/cha" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_tap", "tap");
        add_action("do_tap", "knock");
        add_action("do_sit", "sit");
}

int do_tap(string arg)
{

        object me;
        object susu;

        if (arg != "desk" && arg != "table")
                return notify_fail("你要敲什麼？\n");

        me = this_player();
        if (! objectp(susu = present("su su", environment(me))))
                return notify_fail("你敲了敲桌子，卻還是沒人理你。你突然"
                                   "感覺自己很無聊。\n");

        if( !query_temp("marks/sit", me) )
                return notify_fail("你敲了敲桌子，卻發現素素看著你直笑，"
                                   "你突然感覺自己很愚蠢。\n");

        if( query_temp("marks/served", susu) )
        {
            message_vision("素素不耐煩地對$N說道：我這裡忙著呢！\n", me);
            return 1;
        }

        message_vision("$N端坐在桌前，輕輕扣了下桌面，素素一笑，過來招呼。\n", me);

        susu->serve_tea(me);

        set_temp("marks/served", 1, susu);
        call_out("delete_served", 5, susu);

        return 1;
}


void delete_served(object me)
{
        if (objectp(me))
                delete_temp("marks/served", me);
}


int do_sit(string arg)
{

        if (arg != "chair")
                return notify_fail("你要坐什麼上面？\n");

        if( query_temp("marks/sit", this_player()) )
                return notify_fail("你已經有了個座位了。\n");

        set_temp("marks/sit", 1, this_player());
        write("你找了個空位座下，等著上茶。\n");
        return 1;
}


int valid_leave(object me,string dir)
{
        delete_temp("marks/sit", me);
        delete_temp("tea_cup", me);
        return::valid_leave(me,dir);
}
