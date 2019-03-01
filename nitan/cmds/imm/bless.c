#include <ansi.h>

inherit F_CLEAN_UP;

string *color = ({
    RED, GRN, YEL, BLK, MAG, BLU, CYN, WHT, 
    HIR, HIG, HIY, HIB, HIM, HIC, HIW, });
string *color1 = ({
    RED, GRN, YEL, MAG, BLU, CYN, 
    });

void input_number(string arg);
void show_emote(string* arg,string text);

string *pic = ({ @TEXT
        __   __
       /  \./  \/\_
   __{^\_ _}_   )  }/^\
  /  /\_/^\._}_/  //  /
 (  (__{(@)}\__}.//_/__A____A_______A_____A_____A_____A___A___A______
  \__/{/(_)\_}  )\\ \\---v-----V-----V---Y--v----Y----v---V-----v---
    (   (__)_)_/  )\ \>
     \__/     \__/\/\/
        \__,--'


TEXT,
@TEXT
 .        *                  . . . .  .   .  + .
            "You Are Here" .   .  +  . . .
.                 |      .  .   .    .    . .
                  |     .    .    . +.    +  .
                 \|/            .       .   . .
        . .       V          .    * . . .  .  +   .
           +     ☆           .   .      +
                            .       . +  .+. .
  .                      .     . + .  . .     .      .
           .      .    .     . .   . . .
      *             .    . .  +    .  .           .
          .     .    .  +   . .  *  .       .
               . + .  .  .  .. +  .
.      .  .  .  *   .  *  . +..  .            *
 .      .   . .   .   .   . .  +   .    .            +
TEXT,
@TEXT
 ..           .           .        .     .   .
  *     \     |   /               + . :      *   .            .    *
  .   ---   /    \   ---       .     .   . .     .     *       .
   .       | ~  ~ |        .        . . . .  .   .  + .
      ---   \__O_/   ---         :     .   .  +  . . .
     .      /  |    .  . .     . .   .   .   . .   +  .     +
   .   *  . .      . .    . .  +    .  ...     - O -. .
          .     . + .  .  .  .. +  ..       . / |
 ..      .  .  .  *   .  *  . +..  .            *
  .      .   . .   .   .   . .  +   .    .            +

  .      .   . .   .   .   . .  +   .    .            +

                                   .&______~*@*~______&.           *
                                 "w/%%%%%%%%%%%%%%%%%%%\w"        ***
      __/M__                    p-p_|__|__|_____|__|__|_q-q      **Y**
 ____|O_^_O|___________________[EEEEM==M==MM===MM==M==MEEEE]-__....|....

    ＤＯ ＹＯＵ ＦＥＥＬ ＴＨＥ ＬＯＶＥ ＴＯＮＩＧＨＴ？
TEXT,
@TEXT

             * *   * * *   * *
            *    *    *  *    *
        <========     *==     *==<<<<<<
             *       *       *
               *   *   *   *
                 *       *


TEXT,
@TEXT
            ...  :``..':
             : ````.'   :''::'
           ..:..  :     .'' :
        ``.    `:    .'     :
            :    :   :        :
             :   :   :         :
             :    :   :        :
              :    :   :..''''``::.
               : ...:..'     .''
               .'   .'  .::::'
              :..'''``:::::::
              '         `::::
                          `::.
                           `::
                            :::.
                 ..:```.:'`. ::'`.
               ..'      `:.: ::
              .:        .:``:::
              .:    ..''     :::
               : .''          ::
                :             ::
                               :
                               :
                               :
                               :
                               :
                               .

TEXT,
@TEXT
         .     .                                   .     .
    ...  :``..':                              ...  :``..':
     : ````.'   :''::'                         : ````.'   :''::'
   ..:..  :     .'' :                        ..:..  :     .'' :
``.    `:    .'     :                     ``.    `:    .'     :
    :    :   :        :                       :    :   :        :
     :   :   :         :                       :   :   :         :
     :    :   :        :                       :    :   :        :
      :    :   :..''''``::.                     :    :   :..''''``::.
       : ...:..'     .''                         : ...:..'     .''
       .'   .'  .::::'                           .'   .'  .::::'
      :..'''``:::::::                           :..'''``:::::::
      '         `::::                           ,         `::::
                  `::.                                      `::.
                   `::                                       `::
                    :::.                                      :::.
         ..:```.:'`. ::'`.                         ..:```.:'`. ::'`.
       ..'      `:.: ::                          ..'      `:.: ::
       ..'      `:.: ::                          ..'      `:.: ::
      .:        .:``:::                         .:        .:``:::
      .:    ..''     :::                        .:    ..''     :::
       : .''         .::                         : .''         .::
        :          .'`::                          :          .'`::
                       ::                                        ::
                       ::                                        ::
                        :                                         :
                        :                                         :
                        :                                         :
TEXT,
@TEXT

                      .      .'
                       :`...' `.,'  '
                   `.  ' .**.  ; ; ':
                   ` ``:`****,'  .' :
                 ..::.  ``**":.''   `.
               .:    `: ; `,'        :
                 `:    `   :         ;
                   :   :   :        ;
                   :    :   :     .:
                    :    :   :..,'  ``::.
                     `....:..'  ..:;''
                     .:   . ...::::
                    ,'''''``:::::::
                              `::::
                                `::.
                                 `::
                          . ,.    ::::'      ,..
                        .'.'  ``.  ::      .'.. `.
                       '        .: ::    ,'.'     .
                     .' ,'    .::::::   ,.'    .:::.
                   .' .'  ..:'     ::: .,   .;'     ~
                  ,;::;.::''        ::.:..::'
                 ~                  ::;'
                 ~                  ::;'
                                    ::
                                  ,:::
                                    ::.
                                    `::
                                     ::
                                     ::
                                     ::
                                     ::
TEXT, });

int main(object me,string arg)
{
    object male, female, env;
    string id1, id2, name1, name2;

       if (! SECURITY_D->valid_grant(me, "(immortal)")) 
               return 0; 
    env = environment(me);

    if( !arg || sscanf(arg, "%s with %s", id1, id2) != 2 )
        return notify_fail("指令格式：mbless MALE with FEMALE\n");

//    if( !objectp(male = get_object( id1 ) ) 
//        || !objectp(female = get_object ( id2 ) ) )
    if(!objectp(male = present(id1, environment(me))) ||
       !objectp(female = present(id2, environment(me))))
        return notify_fail("這裡沒有這兩個人哦~~\n");

    if ( ! living( male ) || ! living (female) )
        return notify_fail("看清楚點，那不是活的。\n");
    if( (query("gender", male) != "男性" && query("gender", male) != "雄性" )
        ||(query("gender", female) != "女性" && query("gender", female)!="雌性"))
        return notify_fail("老兄，不要錯點鴛鴦哦~\n");

    name1=query("name", male);
    name2=query("name", female);

    if( (query("qi", me)<100) || 
        (query("jing", me)<100) || 
        (query("neili", me)<100) )
        return notify_fail("你沒有精神祝福人家了 !\n");
    set("qi", 10, me);
    set("jing", 10, me);
    set("neili", 10, me);

//if( !query("env/score", me) )
    message_vision(HIY"$N虔誠地雙手合十，默默地祈禱道：愛神\n"
            "呀，請賜予" + name1 + "和" +
            name2 + "幸福吧！願他們會\n"
            "永遠相親相愛，互相扶持，愛火永不熄滅！\n",
                me);
    call_out("show_picture", 2 + random( 3 ), name1, name2);
    return 1;
}

void show_picture(string name1, string name2)
{
    string str;
    str = HIW "只聽見東方轟隆隆地響了一聲，一個姣美的女聲\n"
        "響起：\n\t" HIM + name1 + 
       NOR "" BLU "和" NOR "" HIM + name2 + NOR "" BLU"將在我的庇護下永遠\n"
        "幸福！我以愛神的名義起誓！\n\n\n" NOR;
    message("marry",str, users());
    call_out("show_flower", 2, name1, name2);
}

void show_flower(string name1, string name2)
{
    string str;
    str = "天空中突然閃出一道絢麗的火花，一個巨大的圖案逐漸\n"
          "顯現：\n";
    str += color1[random(sizeof(color1))] + pic[random(sizeof(pic))] + NOR;
    str += YEL "四下裡隱隱傳來眾人深沉的祝福聲：\n"
        "     “"HIM + name1 + NOR""YEL"和"NOR""HIM +
        name2 + NOR""YEL"永遠幸福...\n"
        "                                           永遠幸福！！”\n\n\n";
    message("marry", str, users());
    if ( random( 2) )
        call_out( "show_flower",2 + random ( 3 ),name1,name2 );
}
