inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這裡是一片茂密的樹林(wood)，翠綠色的樹陰遮蓋著天空，偶爾
還從林子深處傳來幾聲不知什麼野獸的嘶叫。旁邊立著一張木牌(pai
)。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "west"  : __DIR__"shulin1",
                "south" : __DIR__"shanlu1",
        ]));
        set("quarrys", ([
                "tu"         : 100000,
                "ji"         : 80000,
                "pao"        : 50000,
                "caihuashe"  : 50000,
                "dushe"      : 20000,
                "hu"         : 5000,
                "bao"        : 2000,
                "laohu"      : 2000,
        ]));
        set("item_desc", ([
                "pai"  : "保護樹林  適量砍伐\n",
                "wood" :"一片可砍伐的樹林。\n",
        ]));        
         set("coor/x", -49990);
        set("coor/y", 20000);
        set("coor/z", 0);
        setup();
         // replace_program(ROOM);
}

void init()
{
        add_action("do_cut","cut");
}

int do_cut(string arg)
{
        object me = this_player();
        object ob;
 
        if (! arg || arg != "wood")
                return notify_fail("你要砍什麼？\n");
                
        if (present("chai dao", me))
                return notify_fail("沒有柴刀怎麼砍柴？\n");
                
        if (query_temp("times") == 0)
                return notify_fail("請適量砍伐！\n");
 
        if( query("qi", me)<20 )
                return notify_fail("你的氣太虛弱，不能砍柴！\n");
 
        ob = new("/d/baituo/obj/chai");
        ob->move(environment(me));
        addn("qi", -20, me);
        addn_temp("times", -1);
        message_vision("$N砍了一捆柴，累得夠嗆。\n", me);
        return 1;
}
