inherit ROOM;

void create()
{
        set("short","好漢坡");
        set("long", @LONG
此處連綿十幾裏山勢陡峭，名為好漢坡，山路兩旁種滿了細竹，
翠色橫空景象怡人，不知不覺讓你忘記爬坡的疲勞。坡頂有一座回龍
觀，是展望嶽頂的最佳去處，但見天柱峯青紫插天，如在眼前，而相
去實際上還有五十里。
LONG );
        set("exits", ([
                "northdown": __DIR__"wdbl",
                "southdown": __DIR__"shanlu1",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -370);
        set("coor/y", -220);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}