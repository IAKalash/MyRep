import Test.Hspec
import Morse

main :: IO ()
main = hspec $ do
  describe "String To Morse" $ do
    it "checks the empty line" $ do
        stringToMorse "" `shouldBe` Just []
    it "checks the whole alphabet" $ do
        stringToMorse "abcdefghijklmnopqrstuvwxyz1234567890" `shouldBe` Just [".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"]
    it "checks other symbols" $ do
        stringToMorse "1351,../?\'\'\"\"-=+" `shouldBe` Nothing
    it "returns Morse code" $ do
        stringToMorse "hello" `shouldBe` Just ["....", ".", ".-..", ".-..", "---"]
    it "returns Morse code" $ do
        stringToMorse "HelloWorld" `shouldBe` Just ["....", ".", ".-..", ".-..", "---",".--", "---", ".-.", ".-..", "-.."]
    it "returns Morse code" $ do
        stringToMorse "SOS" `shouldBe` Just ["...", "---", "..."]
    it "returns Morse code" $ do
        stringToMorse "JustAnExample" `shouldBe` Just [".---", "..-", "...", "-", ".-", "-.", ".", "-..-", ".-", "--", ".--.", ".-..", "."]
    it "returns Morse code" $ do
        stringToMorse "MorseAlphabet" `shouldBe` Just ["--", "---", ".-.", "...", ".", ".-", ".-..", ".--.", "....", ".-", "-...", ".", "-"]
  describe "\nMorse To String" $ do
    it "checks the empty line" $ do
        morseToString [" "] `shouldBe` Nothing
    it "checks the whole alphabet" $ do
        morseToString [".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----"] `shouldBe` Just "abcdefghijklmnopqrstuvwxyz1234567890" 
    it "returns Morse code" $ do
        morseToString ["....", ".", ".-..", ".-..", "---"] `shouldBe` Just "hello"
    it "returns Morse code" $ do
        morseToString ["....", ".", ".-..", ".-..", "---",".--", "---", ".-.", ".-..", "-.."] `shouldBe` Just "helloworld"
    it "returns Morse code" $ do
        morseToString ["...", "---", "..."] `shouldBe` Just "sos"
    it "returns Morse code" $ do
        morseToString [".---", "..-", "...", "-", ".-", "-.", ".", "-..-", ".-", "--", ".--.", ".-..", "."] `shouldBe` Just "justanexample"
    it "returns Morse code" $ do
        morseToString ["--", "---", ".-.", "...", ".", ".-", ".-..", ".--.", "....", ".-", "-...", ".", "-"] `shouldBe` Just "morsealphabet"
  describe "\nChar To Morse" $ do
    it "checks symbol \'M\'" $ do
        charToMorse 'M' `shouldBe` Just "--"
    it "checks symbol \'Ъ\'" $ do
        charToMorse 'Ъ' `shouldBe` Nothing
  describe "\nMorse To Char" $ do
    it "checks the empty line" $ do
        morseToChar "" `shouldBe` Nothing  