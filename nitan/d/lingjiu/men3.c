inherit ROOM;

void create()
{
        set("short", "閉關室大門");
        set("long", @LONG
這是閉關室南邊，北面有一扇大門便是通往閉關室。那裡本是天
山童姥閉關修練的地方，至天山童姥仙去之後，虛竹子便將此處挪出，
讓梅蘭竹菊四姐妹居住。
LONG );
        set("outdoors", "lingjiu");
        set("exits", ([
                "north" : __DIR__"biguan",
                "south" : __DIR__"xiaodao2",
        ]));
        set("objects",([
                CLASS_D("lingjiu") + "/shisao" : 1,
        ]));
        setup();
        replace_program(ROOM);
}