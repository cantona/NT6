//Room: /d/dali/cangshan.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","蒼山");
        set("long", @LONG
蒼山之腹盛產奇石，世稱大理石，又名點蒼石、文石、礎石。石
質細膩，色彩豐富，有彩花、水墨、銀灰、雪白等品種。水墨最為稀
有，彩花獨具特點，常用於作屏風觀賞，有云樹山川、人物鳥獸之形，
姿態萬千，渾樸天成，為世所寶。銀灰石是精美的建築材料，用於貼
牆鋪地，光潤冰亮，氣若雲水，消暑生涼。雪花石又名點蒼白玉，晶
瑩可愛，白如截脂，是雕刻、繪畫的好材料。石本以產於大理而得名，
而今天下凡此種花石皆稱大理石，『大理』也因此石而名揚天下。
LONG );
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "north"     : "/d/dali/shilin",
            "east"      : "/d/dali/hongsheng",
            "southwest" : "/d/dali/xiaguan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19160);
	set("coor/y", -6820);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}