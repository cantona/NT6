// Room: /yangzhou/pingshantang.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short","平山堂");
        set("long",@LONG
平山堂為歐陽修任揚州知州時建，堂北檐有貴州巡撫林肇元題“遠
山來與此堂平”匾額，闡明堂名。堂中懸方頤書“平山堂”匾，東側題
書“坐花載月”匾，取意於歐陽修遣人持荷行酒載月故事。西側為“風
流宛在”匾。兩側懸掛朱公純(lian)與汪國禎(lian1) 聯。卷廊上懸“
放開眼界”匾，兩側懸掛嘉慶揚州知府伊秉綬聯(lian2)。
    平山堂兩廊壁間有東坡石刻(ke)，前庭植有瓊花一株，紫藤兩株，
歐公柳、春梅、蠟梅、紫薇各一株，以期四季花香。堂後庭院古柏遮天，
東西沿牆磚砌方形花台，栽植歲寒二友——天竹、臘梅，象徵着歐蘇情
誼。
LONG );
        set("item_desc", ([
                "lian" : HIC"
        曉起憑欄，六代青山都到眼
        晚來對酒，二分明月正當頭
\n"NOR,
                "lian1" : HIC"
        山色湖光歸一覽
        歐公坡老峙千秋
\n"NOR,
                "lian2" : "
        過江諸山到此堂下
        太守之宴與眾賓歡
\n",
                "ke" : "
宋元豐二年蘇東坡三至揚州，憶及歐陽修的感慨之作《西江月·平山堂》

三過平山堂下，半生彈指聲中，十年不見老仙翁，上龍蛇飛動。
欲弔文章太守，仍歌楊柳春風，莫言萬事轉頭空，未轉頭時皆夢。
\n",
        ]));
        set("objects", ([
                "/d/huashan/npc/youke" : 1,
        ]));
        set("exits", ([
                "east"  : __DIR__"yongdao",
                "north" : __DIR__"gulintang",
        ]));
        set("coor/x", -40);
        set("coor/y", 160);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}