// Code of ShenZhou
// Ryu, 5/10/97

inherit ROOM;

void create()
{
        set("short", "山巒");
        set("long", @LONG
冰山下的山巒上，成片的塔鬆，墨綠茂密，亭亭玉立，宛若巨傘，
遮天蔽日。密林深處，野草如茵，山花絢麗，鳥聲啁鳴。巨石穿空的
湖畔，涼亭、綠頂黃牆，赫然而立。一泓清冽的湖水，綠盈盈的如碧
玉一般。不時一隻水鳥掠過湖面，掀起白色的浪花，攪碎了倒映的天
光雲影、青山塔鬆。
LONG );
        set("exits", ([
                "eastdown" : "/d/xingxiu/tianchi",
        ]));
        set("bing_can", 7);
        set("cost", 4);
        set("resource/water",1);
        set("fjing", 1);
        set("outdoors", "tianshan");

        setup();
        replace_program(ROOM);
}