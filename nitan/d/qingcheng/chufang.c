// d/qingcheng/chufang.c
//
inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
這是青城山的廚房，收拾得異常乾淨。中央擺着大圓桌，桌上擺着
一些點心和茶水，周圍則放着幾張竹椅。窗口還擺着幾盆山野鮮花。平
時青城山的弟子和家眷都在這裏用餐。
LONG );
        set("exits",([
                "south" :__DIR__"zoulang3",
        ]));
        set("objects",([
                __DIR__"obj/laitangyuan" : random(3)+1,
                __DIR__"obj/kudingcha" : random(2)+1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -8090);
        set("coor/y", -830);
        set("coor/z", 90);
        setup();
        replace_program(ROOM) ;
}