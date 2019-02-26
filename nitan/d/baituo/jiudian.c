inherit ROOM;

void create()
{
        set("short", "酒店");
        set("long", @LONG
這裏是一家獨具特色的酒店，由於地處白駝山下，酒店可以供應
風味食品。許多中原來客都愛來嚐嚐鮮，所以酒店生意興隆。酒店還
經營打散裝酒的業務。
LONG );
        set("exits", ([
                "north" : __DIR__"xijie",
        ]));
        set("objects",([
                "/d/baituo/npc/xiaoer" : 1,
        ]));
        set("resource/water", 1);
        set("coor/x", -49970);
        set("coor/y", 19970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}