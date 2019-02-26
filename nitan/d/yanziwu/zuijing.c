//ROOM: /d/yanziwu/zuijing.c

inherit ROOM;

void create()
{
        set("short", "綴錦樓");
        set("long", @LONG
地面鋪着大紅地毯，房中佈置得珠光寶氣，各種珠寶，古玩擺放
得琳琅滿目，你看了頗為心動，很想順手拿走幾件，但又有些不敢。
角落裏有一架紅木樓梯。
LONG );
        set("exits", ([
            "west" : __DIR__"canheju",
            "east" : __DIR__"jiashan",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}