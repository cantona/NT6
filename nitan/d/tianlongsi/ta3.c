inherit ROOM;

void create()
{
        set("short", "舍利塔");
        set("long", @LONG
這是天龍三塔之一，建於唐初，年代久遠。雖然塔身已經石跡斑
駁，但是仍然聳立挺拔，儼然是天龍寺百年威名的象徵。
LONG );
        set("outdoors", "tianlongsi");
        set("exits", ([
                "east" : __DIR__"talin",
        ]));
        set("objects",([
                "/d/wudang/npc/guest" : 2,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}