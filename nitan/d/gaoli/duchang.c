// /d/gaoli/duchang
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "高麗賭場");
        set("long", @LONG
這裡是高麗城最大的一家賭坊。當夜幕降臨後，這裡就格外熱鬧。
布置豪華的大廳裡，充滿了溫暖和歡樂，酒香中混合著上等脂粉的香氣，
銀錢敲擊，發出一陣陣清脆悅耳的聲音。
LONG        
       );
set("exits", ([
                "east":__DIR__"zhuque-2",    
        ]));
       setup();
        replace_program(ROOM);
}
