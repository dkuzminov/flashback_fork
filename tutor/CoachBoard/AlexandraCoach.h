#pragma once

#include "CoachBoard/BaseCoach.h"
#include "interface/IRepository.h"

class QuestionTOMObject : public QObject
{
    Q_OBJECT

public:
    QuestionTOMObject() {}

public slots:
    virtual QString getWord() = 0;
    virtual void onchange(QString value) = 0;
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
    AlexandraCoach(IRepository::IProfile &profile);

private:
    class QuestionStep : public BaseCoach::StepPage,
                         private QuestionTOMObject
    {
        // ICoach::IStep:
        QObject* GetTOMObject() { return this; }

        // QuestionTOMObject:
        QString getWord() { return m_word; }
        void onchange(QString value);
    public:
        QuestionStep(IAlexandraCoach &owner, size_t index, const QString &type, const QString &html, QString word, QString correctAnswer)
            : BaseCoach::StepPage(type, word, html),
              QuestionTOMObject(),
              m_owner(owner),
              m_index(index),
              m_word(word),
              m_correctAnswer(correctAnswer) {}
    private:
        IAlexandraCoach &m_owner;
        size_t m_index;
        QString m_word;
        QString m_correctAnswer;
    };

    class SummaryStep : public BaseCoach::StepPage,
                        private SummaryTOMObject
    {
        // ICoach::IStep:
        QObject* GetTOMObject() { return this; }

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

        void signalChanged(int correct, int mistakes)
        {
            m_correct = correct;
            m_mistakes = mistakes;
            changed();
        }
    private:
        IAlexandraCoach &m_owner;
        int m_correct;
        int m_mistakes;
    };

    void PrepareLesson();

    IRepository::IProfile &m_profile;
    SummaryStep *m_summaryStep;
    std::vector<int> m_results;
};
