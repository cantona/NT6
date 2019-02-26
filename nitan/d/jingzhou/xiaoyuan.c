inherit ROOM;

void create()
{
        set("short", "卉園");
        set("long", @LONG
這裏是一處幽靜的環境所在，偶爾聽到外面竹林中傳來幾聲清脆
的鳥叫，園子裏種着各式各樣的珍奇花草。有綠菊，蘭花，杜鵑、牡
丹……
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "out" : "/d/jingzhou/zizhulin1"
        ]));
        set("objects",([
                "/d/jingzhou/obj/lvju" : 3,
                "/d/jingzhou/npc/obj/juhua" : 1,
        ]));

        set("coor/x", -7091);
	set("coor/y", -2101);
	set("coor/z", -11);
	setup();
        replace_program(ROOM);
}