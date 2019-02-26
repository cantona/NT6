// Room: /tangmen/bdajie2.c

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long",
"一條筆直的大理石街道，直通北門，兩邊沒有什麼店鋪，只有你孤獨\n"
"的影子伴隨着你。此處一走就可闖蕩江湖了，沒有牽掛的你會一路平安嗎！\n"
"你要自己多多小心了。一路保重！\n"
);
        set("outdoors", "tangmen");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : "/d/xuedao/sroad1",
                "south" : __DIR__"bdajie1",
        ]));

        setup();
        replace_program(ROOM);
}
