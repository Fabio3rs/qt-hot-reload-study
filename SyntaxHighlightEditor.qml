import QtQuick 2.15
import QtQuick.Controls 2.15

TextArea {
    id: textArea
    width: parent.width
    height: parent.height
    font.pixelSize: 14
    wrapMode: TextArea.Wrap
    selectByMouse: true
    textFormat: Qt.RichText;

    property bool highlightingInProgress: false

    // Syntax highlighting
    onTextChanged: {
        if (highlightingInProgress) {
            return;
        }

        highlightingInProgress = true;

        var currentCursorPosition = textArea.cursorPosition;

        var text = textArea.getText(0, textArea.length);
        var newText = "";
        var index = 0;

        // Regular expression to match C++ keywords
        var keywordPattern = "\\b(char|class|const|double|enum|explicit|float|int|long|namespace|short|signed|struct|template|typedef|unsigned|void)\\b";
        var keywordRegExp = new RegExp(keywordPattern, "g");

        var matched = null;
        var changedCounter = 0;

        while ((matched = keywordRegExp.exec(text)) !== null) {
            var startIndex = matched.index;
            var keyword = matched[0];
            var endIndex = startIndex + keyword.length;

            const textTmp = text.substring(index, startIndex);
            newText += textTmp;
            newText += "<font color='#C87532'>" + keyword + "</font>";

            index = endIndex;
            ++changedCounter;
        }

        if (changedCounter === 0) {
            highlightingInProgress = false;
            return;
        }

        newText += text.substring(index);

        textArea.text = newText;

        textArea.cursorPosition = currentCursorPosition;

        highlightingInProgress = false;
    }
}
