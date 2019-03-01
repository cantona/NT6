inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
到得此處，一路上已是風物佳勝。只見路旁仙鶴三二、白
鹿成群，鬆鼠小兔，盡是見人不驚。偶爾聞到陣陣的花香，又
見道旁白兔、小鹿來去奔躍，甚是可愛，令人心曠神怡。
LONG);
        set("outdoors", "jueqing");
        set("exits", ([
               "southdown"   : __DIR__"duanchang",
               "northwest"   : __DIR__"shanlu8",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}