inherit ROOM;

void create()
{
        set("short", "廂房");
        set("long", @LONG
這是絕情谷主之女公孫綠萼的閨房，靠窗一邊是個精致的
梳妝櫃，上面放著一面古銅鏡和一些胭脂水粉。
LONG);
        set("exits", ([
               "west"    : __DIR__"changlang3",
        ]));

        set("objects", ([
                __DIR__"npc/lve" : 1,
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}