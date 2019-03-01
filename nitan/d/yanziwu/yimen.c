//ROOM: /d/yanziwu/yimen.c

inherit ROOM;

void create()
{
        set("short", "儀門");
        set("long", @LONG
一扇朱漆的雕花大門，一塊醒目的牌子掛於門上，上鐫黑色小篆
寫的 "儀門" 二字，給人一種莊嚴威武的感覺。東面就是燕子塢門人
休息的地方，向西則是慕容家人用飯的啖糯廳。
LONG );
        set("exits", ([
            "west"  : __DIR__"qinfang1",
            "east"  : __DIR__"dannuo",
            "north" : __DIR__"longfeng",
            "south" : __DIR__"canheju",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}