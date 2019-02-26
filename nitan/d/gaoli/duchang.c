// /d/gaoli/duchang
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "高麗賭場");
        set("long", @LONG
這裏是高麗城最大的一家賭坊。當夜幕降臨後，這裏就格外熱鬧。
佈置豪華的大廳裏，充滿了温暖和歡樂，酒香中混合着上等脂粉的香氣，
銀錢敲擊，發出一陣陣清脆悦耳的聲音。
LONG        
       );
set("exits", ([
                "east":__DIR__"zhuque-2",    
        ]));
       setup();
        replace_program(ROOM);
}
