//ROOM: /d/yanziwu/shangyu.c

inherit ROOM;

int do_jump(string);

void create()
{
        set("short", "賞魚台");
        set("long", @LONG
站在台上，你可以看見一片荷花菱角，不時有幾尾金魚躍出水面，
有的甚至還跳你眼前，彷彿一伸手就可以抓住。透過荷葉隱約可以看
到船塢，你不知是否有把握能跳過去。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
            "north": __DIR__"shuwu",
        ]));

        setup();
}