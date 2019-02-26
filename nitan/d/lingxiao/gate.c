#include <ansi.h>;

inherit ROOM;

void close_bridge();
int do_open(string arg);

void create()
{
        set("short", "凌霄內門");
        set("long", 
"這裏是凌霄城的城門。本來凌霄城少有外敵入侵，但由於地
處西域，隆冬之際常有餓狼前來侵襲，故修築此大城以做為抵擋。
向城內望去，只見人頭攘攘，很是繁華，想不到在這西域雪山絕
頂，卻有着一個如此去處。內門前那張厚厚的吊橋(bridge)正緊
緊關閉着。如果想要進入的話，必須要請人開(open)才行。
\n");

        set("outdoors", "lingxiao");
        set("exits", ([
                "eastup"  : __DIR__"walle1",
                "westup"  : __DIR__"wallw1",
                "north"  : __DIR__"iceroad1",
        ]));
        set("objects", ([
                CLASS_D("lingxiao") + "/wenwanfu" : 1,
                __DIR__"npc/dizi" : 3,
        ]));
        set("item_desc", ([
                "bridge" : WHT "\n這是一張極大的吊橋，乃是凌霄城的一道防線。\n" NOR,
        ]) );
        setup();
} 

void init()
{
        add_action("do_open", "open"); 
        add_action("do_close", "close");
} 

void close_bridge()
{
        object room;

        if (!( room = find_object(__DIR__"shanya")) )
                room = load_object(__DIR__"shanya");
        if (objectp(room))
        {
                delete("exits/south");
                message("vision", HIY "幾位凌霄弟子上前把吊橋關了起來。\n"
                                  NOR, this_object());
                delete("exits/north", room);
                message("vision", HIY "只聽“嘎嘎嘎嘎”幾聲，吊橋又被關了"
                                  "起來。\n" NOR, room);
        }
}

int do_close(string arg)
{
        if (! query("exits/south"))
                return notify_fail("吊橋已經是關着的了。\n");

        if (!arg || (arg != "bridge" && arg != "south"))
                return notify_fail("你要關什麼？\n");

        message_vision(HIY "$N" HIY "朝凌霄弟子招了一下手，幾位弟子點了點"
                       "頭，上前將吊橋吊了上去。\n" NOR, this_player());

        remove_call_out("close_bridge");
        call_out("close_bridge", 2);

        return 1;
}

int do_open(string arg)
{
        object room;

        if (query("exits/south"))
                return notify_fail("吊橋已經放下來了。\n");

        if (! arg || (arg != "bridge" && arg != "south"))
                return notify_fail("你要開什麼？\n");

        if (! ( room = find_object(__DIR__"shanya")) )
                room = load_object(__DIR__"shanya");
        if (objectp(room))
        {
                set("exits/south", __DIR__"shanya");
                message_vision(HIY "$N" HIY "讓凌霄弟子把吊橋放了下來。\n" NOR, this_player());
                set("exits/north", __FILE__, room);
                message("vision", HIY "只聽“嘎嘎嘎嘎”幾聲，吊橋被放了下來。\n" NOR, room);
                remove_call_out("close_bridge");
                call_out("close_bridge", 10);
        }

        return 1;
}

int valid_leave(object me, string dir)
{
            object *inv;
        mapping myfam, mygen;
        int i;

        myfam=query("family", me);

            if ((! myfam || myfam["family_name"] != "凌霄城" ) && dir == "north")
        {
                inv = all_inventory(me);
                for( i = sizeof(inv)-1; i >= 0; i--)

                    if( query("weapon_prop", inv[i]) && query("skill_type", inv[i]) && 
                          query("equipped", inv[i]) )

                if (objectp(present("wen wanfu", environment(me))))
                            return notify_fail(CYN "聞萬夫身形一展，擋住你道：凌霄城歷年"
                                           "來的規矩，外人入城不得佩帶兵刃。\n");
            }
            return ::valid_leave(me, dir);
}