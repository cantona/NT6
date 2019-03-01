// Room: /wuliang/zhengting.c
// Date: Oct.18 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "練武廳");
        set("long", @LONG
練武廳東坐著二人。上首是個四十左右的中年道姑，鐵青著臉，
嘴唇緊閉。下首是個五十余歲的老者，右手捻著長須，神情甚是得意。
兩人的座位相距一丈有余，身後各站著二十余名男女弟子。
LONG );
        set("exits", ([
                "southdown"  : __DIR__"road1",
                "east"       : __DIR__"road2",
                "west"       : __DIR__"road3",
                "north"      : __DIR__"road4",
        ]));
        set("objects", ([
                __DIR__"npc/zuo"  : 1,
                __DIR__"npc/xin"  : 1,
                __DIR__"npc/gong" : 1,
                __DIR__"npc/qi" : 1,
        ]));
        set("coor/x", -71000);
        set("coor/y", -79890);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}