inherit ROOM;

void create()
{
        set("short", "金殿");
        set("long", @LONG
金殿中間供著真武大帝銅像，披發跣足，體態豐滿；左右有金童
玉女侍立，虔誠恭敬；水、火二將，威武莊嚴。殿前供器皆為銅鑄。
殿宇和殿內銅像、供桌鉚焊一體，構件精確，技巧高超。
LONG );
        set("exits", ([
                "north" : __DIR__"zijincheng",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -440);
        set("coor/z", 180);
        setup();
        replace_program(ROOM);
}