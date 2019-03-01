// /d/gaoli/dangpu
// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "高麗當舖");
        set("long", @LONG
你走進了高麗的當舖，這裡略現昏暗，當前巨大的櫃台用手指粗細
的鐵欄桿圍著，一副小心謹慎的模樣，老板是個很精明的生意人，見你
走了進來，很客氣地和你寒暄，但眼睛裡卻沒有什麼笑意，很審慎地打
量著你。
LONG
          );
set("exits", ([
                "west":__DIR__"zhuque-2",    
        ]));
 set("objects", ([
                "/d/gaoli/npc/jin1" : 1,
        ]));
       setup();
        replace_program(ROOM);
}
