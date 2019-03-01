inherit ROOM;

void create()
{
        set("short", "福壽庵");
        set("long", @LONG
福壽庵在神水庵南，是一個名叫天性的僧人建造的。庵前有九曲
渠、流杯池，古人曾據在此飲酒流杯觀景賦詩，歌詠興嘆不知夕日。
庵旁有株海棠樹，數百蒼齡高達十余丈。
LONG );
        set("objects", ([
                CLASS_D("emei") + "/zhen" : 1,
                __DIR__"npc/girldizi" : 1,
        ]));
        set("exits", ([
                "enter" : __DIR__"lingwenge",
                "north" : __DIR__"shenshuian",
        ]));
        set("outdoors", "emei");
        set("coor/x", -440);
        set("coor/y", -240);
        set("coor/z", 70);
        setup();
        replace_program(ROOM);
}