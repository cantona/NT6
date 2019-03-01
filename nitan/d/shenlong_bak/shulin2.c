// /d/shenlong/shulin2 樹林
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        int i;
        set("short", "樹林");
        set("long", @LONG
樹林裡光線暗淡，只能聽見頭頂上傳來一些鳥兒的啼鳴。偶爾從茂
密的葉間透過的一線光伴著落葉在飛舞。朽木腐爛的氣味和身後傳來蛇
蟲爬行的聲音使人不覺猶豫了前進的腳步。
LONG
        );
        i = random (3);
        switch (i)
        {
                case 0:
                        set("objects", ([
                                "/d/city/obj/shuzhi" : 1,
                                "/d/jiaxing/npc/wuya" : 1,
                        ]));
                        break;
                case 1:
                        set("objects", ([
                                "/d/city/obj/shuzhi" : 1,
                                "/d/wudang/npc/yetu" : 1,
                        ]));
                        break;
                case 2:
                        set("objects", ([
                                "/d/city/obj/shuzhi" : 1,
                                "/d/shenlong/npc/snake" : 1,
                        ]));
                        break;
        }
        set("exits", ([
                "west" : __DIR__"yutang",
                "south" : __DIR__"shulin1",
        ]));
        set("outdoors", "shenlong");

        setup();
        replace_program(ROOM);
}
