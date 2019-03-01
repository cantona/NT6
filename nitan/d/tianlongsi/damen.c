inherit ROOM;

void create()
{
        set("short", "大門");
        set("long", @LONG
你來到了天龍寺大門前，只見氣勢恢弘的兩個大門柱上刻有一付
對聯( duilian )，紅漆覆字，頗有點撥眾生之意。抬頭上望，門楣上
一塊黑木大匾，上題『崇聖寺』三個大字，筆意蒼鬆。此乃正式寺名，
但大理百性叫慣了，都稱之為『天龍寺』。
LONG );
        set("outdoors", "tianlongsi");
        set("exits", ([
                "south" : __DIR__"talin",
                "north" : "/d/dali/hongsheng",
        ]));
        set("item_desc",([
                "duilian" : "\n    心性無染本自圓成　但離妄緣即如如佛\n\n",
        ]));        
        set("objects",([
                "/d/wudang/npc/guest" : 1,
        ]));
        setup();
        replace_program(ROOM);
}