inherit ROOM;

void create()
{
        set("short", "冰道");
        set("long", @LONG
這裡是凌霄城的南街，凌霄城的弟子、親人、家屬，盡皆居
住在城裡。凌霄城自創派以來一百余年，歷代先祖皆是飽學逍遙
之士，以老子之黃庭為銘，避人間之煩囂，享高處之清寒，是以
凌霄弟子居此西域冷僻之地，仍能生生不息。這裡人來人往，西
面是一家刀劍舖，東邊是一家藥舖。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
                    "south" : __DIR__"iceroad1",
                    "north" : __DIR__"iceroad3",
                    "west"  : __DIR__"wuqi",
                    "east"  : __DIR__"yaodian",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
