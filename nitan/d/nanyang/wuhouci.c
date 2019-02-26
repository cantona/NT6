// Room: /d/nanyang/wuhouci.c
// Last Modified by winder on Nov. 20 2001

inherit ROOM;
void create()
{
        set("short","武侯祠");
        set("long",@LONG
武侯祠乃為三國時期的著名人物，家喻户曉的諸葛亮而建，相傳這
裏即是他的家鄉。進得山門，但見松柏森森，環境幽靜，院子正中一間
八卦亭，彩繪流檐，設計精巧。兩側分別是小巧的鐘，鼓樓，相互呼應
；北面是正殿。
LONG);
        set("exits",([
                "southwest" : __DIR__"dajie2",
                "north"     : __DIR__"zhengdian",
        ]));
        set("outdoors","nanyang");
        set("no_clean_up", 0);
	set("coor/x", -6930);
	set("coor/y", 790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}