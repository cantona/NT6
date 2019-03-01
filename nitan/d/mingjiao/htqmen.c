//HTQMEN.C

inherit ROOM;

void create()
{
        set("short", "厚土旗門");
        set("long", @LONG
這是厚土旗的洞門，門洞裡進進出出的厚土旗眾，身上掛滿了鍬，
鏟，短刀，誰也不理你。門邊兩面短桿鑲黃邊飛龍旗，繡著厚土二字。
LONG );
        set("exits", ([
                "enter" : __DIR__"htqdating",
                "south" : __DIR__"tohtq7",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}