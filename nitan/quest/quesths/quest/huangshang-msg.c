#include <ansi.h>

string *action_msg = ({
"黃裳頭也不抬地說：“",
"黃裳翻出一疊檔案道：“",
"黃裳低頭想了想，說道：“",
"黃裳憂心忡忡的說：“",
"黃裳微微笑了笑道：“",
"黃裳斬釘截鐵的說道：“",
"黃裳背著雙手跺著步，一字一字的對你說：“",
"黃裳輕輕嘆息到：“",
"黃裳突發奇想道：“",
});

string *say_msg1 = ({
"我突然想起需要一樣東西，就是name",
"我想這樣子，你不如去找找name",
"你現在就去，快點尋一尋name",
"武林大會就要召開，目前正需要name",
"現在有一件急事要你辦，就是去找來name",
"我這裡正想找人抓差，你去把name",
"你現在去四處看看，有沒有name",
"讓你趕快去做一件事，也就是找name",
"養兵千日，用兵一時，看看你的辦事能力，去搞來name",
"我怎麼還沒有name",
"你難道還不知道我現在需要什麼？name",
"聽說有一樣東西叫name",
"天下大部分東西我都有了，不過少了一樣name",
});

string *say_msg2 = ({
"，你能不能把它找來呢",
"，我想你應該可以完成任務吧",
"，仔細找一找，應該不難的",
"，速速找來交給我要緊",
"，要是能找來，我自會獎勵你",
"，能不能尋到它呢？",
"，找了來就看出你的辦事能力了",
"，速去速回",
"這個物件，快想辦法去吧",
"交給我，怎麼樣，不會太難吧",
});

string *kill_msg1 = ({
"name這個人違背江湖道義，",
"你聽說過name最近出賣朋友的事情麼？",
"人人都說name老是胡作非為，",
"name膽子竟然那麼大？居然也敢辱罵武林同盟！",
"聽說name一心想替我而代之？",
"侮辱朋友的妻子，name是狗膽包天了，",
"有一伙人最近打著我的旗號四處招搖撞騙，我已經查出其中有name，",
"江湖有江湖的道義，name最近的所作所為實在不象話！",
"你去找找看name在什麼地方，殺了我們的兄弟躲起來就行了？",
});

string *kill_msg2 = ({
"這種人豈能活在世界上！”",
"你去殺了這個家伙吧。”",
"對這種人就不要心慈手軟了。”",
"把name送到閻王那裡去吧！”",
"殺了name，幹凈利索點。”",
"為了維持江湖道義，也只有殺了name了。”",
});

string query_hsmsg(string type,string name)
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
        } else
        {
                msg1 = kill_msg1[random(sizeof(kill_msg1))];
                msg1 = replace_string(msg1,"name",name);
                msg2 = kill_msg2[random(sizeof(kill_msg2))];
                msg2 = replace_string(msg2,"name",name);
        }
        msg += msg1;
        msg += msg2;
        return msg;
}
