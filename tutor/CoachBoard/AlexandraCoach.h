#pragma once

#include "CoachBoard/BaseCoach.h"
#include "interface/IRepository.h"

class QuestionTOMObject : public QObject
{
    Q_OBJECT

public:
    QuestionTOMObject() {}

signals:
    void finished();

public slots:
    virtual QString getWord() = 0;
    virtual int getTotalNumber() = 0;
    virtual int getCorrectNumber() = 0;
    virtual int getMistakesNumber() = 0;
    virtual int getSkippedNumber() = 0;
    virtual QString getQuestionedWord(int index) = 0;
    virtual QString getCorrectAnswer(int index) = 0;
    virtual QString getActualAnswer(int index) = 0;
    virtual void onchange(QString value) = 0;
    virtual void onanswer(QString value) = 0;
    virtual void onskip() = 0;
};

class SummaryTOMObject : public QObject
{
    Q_OBJECT

public:
    SummaryTOMObject() {}

public slots:
    virtual int getCorrectNumber() = 0;
    virtual int getMistakesNumber() = 0;

signals:
    void changed();
};


struct IAlexandraCoach
{
    virtual void setAnswerStatus(size_t questionIndex, int status) = 0;
};

class AlexandraCoach : public BaseCoach,
                       private IAlexandraCoach
{
    // IAlexandraCoach:
    void setAnswerStatus(size_t questionIndex, int status);

public:
    AlexandraCoach(repository::IProfile &profile);

private:
    class MultipleQuestionsStep : public BaseCoach::StepPage,
                                  private QuestionTOMObject
    {
        // ICoach::IStep:
        QObject* GetTOMObject() { return static_cast<QuestionTOMObject*>(this); }

        // ICoach::IPageContents:
        const QString& GetTemplate()
        {
            if (m_questionIndex < m_questions.size())
                return BaseCoach::StepPage::GetTemplate();
            return m_htmlResume;
        }

        // QuestionTOMObject:
        QString getWord() { return m_questions[m_questionIndex].first; }
        int getTotalNumber() { return m_questions.size(); }
        int getCorrectNumber() { return m_correct; }
        int getMistakesNumber() { return m_mistakes; }
        int getSkippedNumber() { return m_skipped; }
        QString getQuestionedWord(int index) { return m_questions[index].first; }
        QString getCorrectAnswer(int index) { return m_questions[index].second; }
        QString getActualAnswer(int index) { return m_answers[index]; }
        void onchange(QString value) { throw "Not implemented"; }
        void onanswer(QString value);
        void onskip();
    public:
        MultipleQuestionsStep(IAlexandraCoach &owner,
                              const QString &type,
                              std::vector<std::pair<QString, QString>> questions)
            : BaseCoach::StepPage(type, questions[0].first, x_ReadFileFromResource(":/html/templates/tests/TypeMeaningTest")),
              QuestionTOMObject(),
              m_owner(owner),
              m_questions(questions),
              m_questionIndex(0),
              m_correct(0),
              m_mistakes(0),
              m_skipped(0),
              m_htmlResume(x_ReadFileFromResource(":/html/templates/tests/Resume"))
        {}
    private:
        void x_MoveNext();

        IAlexandraCoach &m_owner;
        std::vector<std::pair<QString, QString>> m_questions;
        std::vector<QString> m_answers;
        size_t m_questionIndex;
        size_t m_correct;
        size_t m_mistakes;
        size_t m_skipped;
        QString m_htmlResume;
    };

    class SummaryStep : public BaseCoach::StepPage,
                        private SummaryTOMObject
    {
        // ICoach::IStep:
        QObject* GetTOMObject() { return static_cast<SummaryTOMObject*>(this); }

        // SummaryTOMObject:
        int getCorrectNumber() { return m_correct; }
        int getMistakesNumber() { return m_mistakes; }
    public:
        SummaryStep(IAlexandraCoach &owner, const QString &type, const QString &html)
            : BaseCoach::StepPage(type, "-", html),
              SummaryTOMObject(),
              m_owner(owner),
              m_correct(0),
              m_mistakes(0)
        {}

        void signalChanged(int correct, int mistakes, int total)
        {
            m_correct = correct;
            m_mistakes = mistakes;
            Update("Test Results", "progress " + QString::number(correct + mistakes) + " out of " + QString::number(total));
            emit changed();
        }
    private:
        IAlexandraCoach &m_owner;
        int m_correct;
        int m_mistakes;
    };

    void PrepareLesson();

    repository::IProfile &m_profile;
    SummaryStep *m_summaryStep;
    std::vector<int> m_results;
};
