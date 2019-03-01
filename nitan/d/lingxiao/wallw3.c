// wallw3.c

inherit ROOM;

void create()
{
        set("short", "城頭");
        set("long", @LONG
“大漠孤煙直，長河落日圓”。也只有在這種絕域寒地，方
有此種豪邁奇景現世。日薄西山，余輝滿世，在這寂靜無聲的大
漠之上，往往有煙氣直升九霄，蔚為奇觀。視野盡處，一道橫貫
大漠的長河，遮掩住了紅火的落日。天色癒暗，直到那最後一道
余輝逝去，短短一柱香的時間內，讓人的靈魂，也為之震撼。 
LONG );
        set("outdoors", "lingxiao");
        set("no_clean_up", 0);

        set("exits", ([
                "east" : __DIR__"wallw2",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 1,
        ])); 
        setup(); 
        replace_program(ROOM);
}
