//Room: /d/suzhou/hong-zoulang.c
// by llm 99/06/12

inherit ROOM;

void create()
{
        set("short", "紅娘莊走廊");
        set("long", @LONG
走廊兩邊是紅漆金粉的廊柱雕欄，高低錯落地挑著兩排紅燈籠。
地上舖著厚厚的大紅地毯，急待結婚的新人們進來踩在上面，一股喜
慶幸福之感自心底油然而生。前面是一個不大的門廳。
LONG );
        set("exits", ([
                "west" : "/d/suzhou/hong-damen",
                "east" : "/d/suzhou/hongniang-zhuang",
   ]) );

   set("objects", ([
           "/d/suzhou/npc/xiao-hongniang" : 1,
      ]) );
   set("coor/x", 220);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
