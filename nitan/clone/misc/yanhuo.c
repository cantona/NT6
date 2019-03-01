//yanhuo.c 燄火

inherit ITEM;
#include <ansi.h>
int fire(object me, object ob);

void create()
{
    set_name(HIM "煙花" NOR, ({"yan hua","yanhua"}));
    set("unit", "個");
    set("long", "這是還未點燃的煙花。\n");
    set("value",1000000);
    setup();
}

int fire(object me, object ob)
{
    object obj=this_object();

    message_vision("$N用" + ob->name() + "點燃了" + name() +"。\n", me);

    message_vision("一道火光沖天而起，“砰”的一聲散開，化作滿天美麗的圖案....\n",me,ob);
    switch(random(15))
    {
        case 0:
        tell_room(environment(me),BLINK+HIM@TEXT

　　　　　　　　|□|□ □□ □ILOVEYOU□□□ □ |永|
　　　　　　　　|□|≒● ☆□□□□□□□☆ ○≒|□|
　　　　　　　　|之| /□\□□□□∥□□□□/□\ |不|
　　　　　　　　|心|★Π※□□ □Ψ□ □□※Π★|□|

TEXT NOR);
        break;

        case 1:
        tell_room(environment(me),BLINK+HIY@TEXT

　　　　　　　　　　　　　　　\\\|///
　　　　　　　　　　　　　　\\　.-.-　//
　　　　　　　　.　　　　　　(　.@.@　)
　　　　　　　　+-------oOOo-----(_)-----oOOo---------+
　　　　　　　　|　　　 　　　　　　　　　　　　　　　|
　　　　　　　　|　    　祝   你   快  樂！！！ 　  　|
　　　　　　　　|　　　　　　　　　　　　　　　　 　　|
　　　　　　　　+---------------------Oooo------------+

TEXT NOR);
        break;

        case 2:
        tell_room(environment(me),BLINK+HIC@TEXT

　　　　　　　　□□□oοΟ□ □□□□ □Οοo□□□
  　　　　　　　　〔雲淡□〕  □封□□  〔□心如〕
  　　　　　　　　〔□風輕〕  □□心□  〔止水□〕
　　　　　　　　    □□□☆□□□□□□☆□

TEXT NOR);
        break;

        case 3:
        tell_room(environment(me),BLINK+HIG@TEXT

　　　　　　　　　□□□oοΟ□□永□□Οοo□□□
　　　　　　　　〔□□□〕 oO天□□□地0o 〔永不..〕
　　　　　　　　〔..一生〕 0o□□□□□o0 〔□後悔〕
　　　　　　　　  □□□□☆□ □□□ □☆□

TEXT NOR);
        break;

        case 4:
        tell_room(environment(me),BLINK+HIR@TEXT

　　　　　　　　□□□□ 我□在最  □□□□□□□
　　　　　　　　□□□□ 大的□望□□□我∥好□□□
　　　　　　　　□□□□ 就是想□ □□ 是∥□ □□
　　　　　　　　  □□   陪著我!!    ★好□□★

TEXT NOR);
        break;

        case 5:
        tell_room(environment(me),BLINK+HIC@TEXT

　　　　　　　　::∴★∵**☆．∴★∵**☆．
　　　　　　　　  □□□□□．☆．∵★∵∴☆．
　　　　　　　　  □田□田□．*☆．∴★∵．
　　　　　　　　  □田□田□．★∵∴☆．★∵∴．
　　　　　　　　  □田□田□．同一個星空下★..**．
　　　　　　　　  □田□田□．望著天空的星星雨**☆．
　　　　　　　　  □□□□□．
　　　　　　　　□□□□□□□．~~~~~*^_^* 

TEXT NOR);
        break;

        case 6:
        tell_room(environment(me),BLINK+HIM@TEXT


　　　　　　　　         ★★ ★★       ★★  ★★
　　　　　　　　▲    ★ ☆☆★☆☆★  ★☆☆★☆☆ ★    
　　　　　　　　■■■■■■■■■■■■■■■■■■■■■═→   
　　　　　　　　▲       ★  ☆ ★      ★  .☆  ★
　　　　　　　　           ★  ★          ★  ★
　　　　　　　　             ★              ★

TEXT NOR);
        break;

        case 7:
        tell_room(environment(me),BLINK+HIR@TEXT

                    * *   * *   *    * *
                  *     *     *   *      *
               <========      *==        *==<<<<<<
                    *       *          *
                      *   *     *    *      
                        *         *

TEXT NOR);
        break;

        case 8:
        tell_room(environment(me),BLINK+HIB@TEXT

　　　　　　　　記得我們的星空嗎？好美！
　　　　　　　　　　　　   . ☆   .   ?  .  ?     .  ? .
　　　　　　　　　　  　     **    .   ?       □    ? 
　　　　　　　　 　　　　 ? ***N   .       ? ｏ    ?  . 
　　　　　　　　 　　  　? *i****     ?  .  o    ?       ?
　　　　　　　　    　　　X***J***         ╴╴□   ＼ ／＼
　　　　　　　　   　　　**X*****o*     ／＼　□＼ 

TEXT NOR);
        break;

        case 9:
        tell_room(environment(me),BLINK+HIB@TEXT

　　　　　　　　∴°★．☆° ．★﹒°∴°★．° ．﹒。∴°
　　　　　　　　☆ ．﹒°∴° ☆．．﹒°∴°．☆°★°∴°
　　　　　　　　°∴ 那怕星際無垠 ☆° ．﹒★°∴°．°°
　　　　　　　　∴°．°★ ．﹒°∴°．°∴°．★☆° ．﹒
　　　　　　　　°．☆° ．★﹒我也要追到你 °．°°．★
　　　　　　　　．﹒°∴★°．°∴°．☆° ．﹒°∴°．°
　　　　　　　　．﹒°∴°★．°．∴﹒°°並永遠愛你∴☆°

TEXT NOR);
        break;

        case 10:
        tell_room(environment(me),BLINK+HIY@TEXT

　　　　　　　　    ☆☆ ☆☆  ☆☆ ☆☆
　　　　　　　　  ★★       ★      ★★
　　　　　　　　 ☆☆     祝你快樂    ☆☆
　　　　　　　　  ★★               ★★
　　　　　　　　   ☆☆             ☆☆
　　　　　　　　     ★★         ★★
　　　　　　　　       ☆☆     ☆☆
　　　　　　　　         ★★  ★★
　　　　　　　　            ☆☆

TEXT NOR);
        break;

        case 11:
        tell_room(environment(me),BLINK+HIC@TEXT

　　　　　　　　□□☆□□☆□□ 送星星千百顆...
　　　　　　　　□☆☆☆☆☆☆□ 
　　　　　　　　□□☆☆☆☆□□ 生命活的精彩燦爛...
　　　　　　　　□□□☆☆□□□ 
　　　　　　　　□□□□□□□□ 願你快樂  ^_^

TEXT NOR);
        break;

        case 12:
        tell_room(environment(me),BLINK+HIG@TEXT

　　　　　　　　@* .☆ / ＊/　.　/ * . ☆/ ＊。
　　　　　　　　   □□。       □□。
　　　　　　　　  □★□。     □★□。
　　　　　　　　 □■■□。   □■■□。
　　　　　　　　□■■■□。 □■■■□。
　　　　　　　　□□||□□ !!□□||□□
　　　　　　　　願您有快樂的每一天

TEXT NOR);
        break;

        case 13:
        tell_room(environment(me),BLINK+HIW@TEXT

　　　　　　　　::.--.-.::
　　　　　　　　:( (    ):::::  東邊日出西邊雨 
　　　　　　　　(_,  \ ) ,_)::  道是無晴卻有情       |
　　　　　　　　:::-'--`--:::::::: ~~|     ,       \ _ /
　　　　　　　　::::::::::::::::::: ,|`-._/|   -==  (_)  ==-
　　　　　　　　::::::::^^::::::::.' |   /||\      /   \
　　　　　　　　::::::^^::::::::.'   | ./ ||`\       |
　　　　　　　　:::::::::::::::/ `-. |/._ ||  \
　　　　　　　　::::::::::::::|      ||   ||   \
　　　　　　　　 ~~=~_~^~ =~ \~~~~~~~'~~~~'~~~~/~~`` ~=~^~
　　　　　　　　~^^~~-=~^~ ^ `--------------'~^~=~^~_~^=~^~

TEXT NOR);
        break;

        case 14:
        tell_room(environment(me),BLINK+HIW@TEXT

　　　　　　　　　★　　 □□　
　　　　　　　　　　　　　　　　　　　　　□□□　　　☆　
　　　　　　　　　　　　　 /○\ ●　　　 □□□□　　　 ┌────┐　
　　　　　　　　　　　　　 /■\/■\　　□□□□□□　　 │兩情相悅│　
　　　　　　　　　 □□□　 <|　||　　□□□□□□□□　└┬──┬┘

TEXT NOR);
        break;
    }
    me->start_busy(1);
    destruct(obj);
    return 1;
}
