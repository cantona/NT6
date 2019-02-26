#include <ansi.h>

string *action_msg = ({
"獨孤求敗微笑着對你説：“",
"獨孤求敗滿臉正容道：“",
"獨孤求敗呵呵大笑着説：“",
"獨孤求敗憂心忡忡的説：“",
"獨孤求敗緩緩的告訴你：“",
"獨孤求敗一臉和藹的説道：“",
"獨孤求敗揹着雙手踱着步，嚴肅的説：“",
"獨孤求敗輕輕歎息到：“",
"獨孤求敗正容對你道：“",
});

string *say_msg1 = ({
"我突然想起需要一樣東西，就是name",
"我想這樣子，你不如去找找name",
"你現在就去，幫我尋一尋name",
"江湖動盪，物資緊缺，我目前正想要name",
"現在有一件急事要你做，就是去幫我找name",
"你有空就去四處看看，是否能弄來name",
"我想請你趕快幫我做一件事，也就是找name",
"年輕人需要多鍛鍊鍛鍊，看看你的辦事能力，去搞來name",
"我突然很想看看name",
"聽説有一樣東西叫name",
"天下大部分東西我都有了，不過少了一樣name",
});

string *say_msg2 = ({
"，你能不能把它找來呢",
"，我想你應該可以完成任務吧",
"，仔細找一找，應該不難的",
"，速速找來交給我要緊",
"，要是能找來，我自會獎勵你",
"，能不能尋到它呢？",
"，能否找來就看出你的辦事能力了",
"，速去速回",
"這個物件，快想辦法去吧",
"交給我，怎麼樣，不會太難吧",
});

string *kill_msg1 = ({
"name這個人素來多行不義，",
"你聽説過name最近犯下的滔天罪行吧？",
"有人向我反映name老是胡作非為，",
"name竟然誘拐良家婦女！",
"聽説name最近幫太行山土匪領路，打劫了一個鎮子，",
"對朋友坑蒙拐騙，name這個人毫無仁義道德，",
"有一夥人最近冒充我四處招搖撞騙，我已經查出其中有name，",
"做錯事情可以改，一錯再錯，我也維護不了name，",
"你去找找name在什麼地方，這個人犯下的罪行連神都不會原諒，",
});

string *kill_msg2 = ({
"這種人多一個不如少一個！”",
"你去剷除了這個惡霸吧。”",
"對這種人就不要心慈手軟了。”",
"把name送到地獄去好好反省吧！”",
"鋤了name，不要心慈手軟！”",
"為了維護江湖的公德，也只有殺了name了。”",
});

string *summon_msg1 = ({
"name這個人本性不壞，我倒是有心維護一下，",
"你聽説過name最近犯了點錯誤吧？",
"有人向我反映name老是胡作非為，",
"name好好一個人，怎麼突然也幹壞事？",
"聽説name最近去過太行山土匪窩，不知道想幹什麼？",
"犯了錯誤，要及時改正啊，name現在需要指引才能走上正道，",
"你去找找name在什麼地方，",
});

string *summon_msg2 = ({
"你把name給我帶這裏來吧！”",
"幫我去把name擒來。”",
"帶name來我這裏，我來教育教育。”",
"不知道name來我這裏會不會聽我的指導！”",
"我真想當面好好的責問一下name！”",
});

string query_dgmsg(string type,string name)
{
        string msg,msg1,msg2;
        msg = "";
        msg1 = "";
        msg2 = "";
        msg += action_msg[random(sizeof(action_msg))];
        if (type == "尋") {
                msg1 = say_msg1[random(sizeof(say_msg1))];
                msg1 = replace_string(msg1,"name",name);
                msg2 = say_msg2[random(sizeof(say_msg2))];
                msg2 = replace_string(msg2,"name",name);
        } else if (type == "殺" || type == "宰")
        {
                msg1 = kill_msg1[random(sizeof(kill_msg1))];
                msg1 = replace_string(msg1,"name",name);
                msg2 = kill_msg2[random(sizeof(kill_msg2))];
                msg2 = replace_string(msg2,"name",name);
        } else if (type == "捉" || type == "擒")
        {
                msg1 = summon_msg1[random(sizeof(summon_msg1))];
                msg1 = replace_string(msg1,"name",name);
                msg2 = summon_msg2[random(sizeof(summon_msg2))];
                msg2 = replace_string(msg2,"name",name);
        }
        msg += msg1;
        msg += msg2;
        return msg;
}
