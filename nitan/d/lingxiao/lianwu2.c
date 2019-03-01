inherit ROOM;

void create()
{
        set("short", "練武廳");
        set("long", @LONG
這裡是凌霄城的練武場。只見刀光劍影，目不暇接，一群凌
霄弟子練得大汗淋漓，彼此打得難解難分。凌霄城裡因派系不和，
彼此間明爭暗鬥，門下弟子也只得努力練功，以防不測。
LONG );
        set("exits", ([
            "west"      : __DIR__"fudian2",
        ]));
        set("outdoors", "lingxiao" );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
