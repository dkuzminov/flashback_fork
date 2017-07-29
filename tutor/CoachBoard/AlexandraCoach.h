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

class ProgressTOMObject : public QObject
{
    Q_OBJECT

public:
    ProgressTOMObject() {}

public slots:
    virtual double getProgress() = 0;

signals:
    void finished();
};


struct IAlexandraCoach
{
    virtual void reportAnswer(const QString &word, bool isCorrect) = 0;
    virtual double getProgress() = 0;
};

class AlexandraCoach : public BaseCoach,
                       private IAlexandraCoach
{
    // IAlexandraCoach:
    void reportAnswer(const QString &word, bool isCorrect);
    double getProgress();

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

    class ProgressStep : public BaseCoach::StepPage,
                         private ProgressTOMObject
    {
        // ICoach::IStep:
        QObject* GetTOMObject() { return static_cast<ProgressTOMObject*>(this); }

        // SummaryTOMObject:
        double getProgress() { return m_owner.getProgress(); }
    public:
        ProgressStep(IAlexandraCoach &owner, const QString &type)
            : BaseCoach::StepPage(type, "-", x_ReadFileFromResource(":/html/templates/tests/Summary")),
              ProgressTOMObject(),
              m_owner(owner)
        {}

        void signalChanged()
        {
            Update("Progress", "progress " + QString::number(getProgress()) + "%");
            emit finished();
        }
    private:
        IAlexandraCoach &m_owner;
    };

    void PrepareLesson();

    repository::IProfile &m_profile;
    ProgressStep *m_progressStep;
};
