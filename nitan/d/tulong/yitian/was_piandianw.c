inherit ROOM;

void create()
{
        set("short", "偏殿");
        set("long", @LONG
這裡是萬安寺的偏殿，本是萬安寺眾僧參禪之處，地上只擺著幾個蒲團。大
台上供著十八羅漢中的九個羅漢，一個個是金光閃閃，栩栩如生。
LONG );
        set("exits", ([
                "east" : "/d/tulong/yitian/was_dadian",
        ]));

        setup();
}
