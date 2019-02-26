#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "大廳" NOR );
        set("long", @LONG
你推門走了進來，原來這裏就是天下聞名的天地會青木堂的大廳
所在，只見一張板桌上供着兩個靈牌，中間一個寫着『大明天子之位
』，側邊一個寫着『大明延平郡王鄭之位』。此外有一塊白木 (baim
u)，上面密密麻麻全是血字。廳側有一副對聯(duilian)。
LONG );
        set("valid_startroom", 1);
        set("exits", ([
        "north" : "/d/beijing/qingmu_fang1",
        ]));
        set("item_desc", ([
"baimu" : 
HIR "\n  只見白木上寫道：天地萬有，回覆大明。吾人當同生共死，\n"
"仿桃園故事，約為兄弟，姓洪名金蘭，合為一家。拜天為父，\n"
"拜地為母, 日為兄，月為姊妹，焚香設誓，一雪前恥，順天\n"
"行道，恢復明朝。歃血為盟，神明降鑑。\n" NOR,
"duilian":
HIC "\n地振高岡，一派溪山千古秀\n" NOR +
HIG "門朝大海，三河合水萬年流\n" NOR,
        ]));
        set("objects", ([
                CLASS_D("yunlong") + "/chen" : 1,
                CLASS_D("yunlong") + "/first" : 1,
        ]));
	set("coor/x", -2820);
	set("coor/y", 7610);
	set("coor/z", 0);
	setup();
        "/clone/board/tiandihui_b"->foo();
}
