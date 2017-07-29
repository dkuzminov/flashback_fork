#include "CoachBoard/AlexandraCoach.h"
#include "Log.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

AlexandraCoach::AlexandraCoach(repository::IProfile &profile)
    : m_profile(profile)
{
    LOG(Note, "Enter AlexandraCoach::AlexandraCoach()");
}

void AlexandraCoach::PrepareLesson()
{
    LOG(Note, "Enter AlexandraCoach::PrepareLesson()");

    auto words = m_profile.GetLanguage().GetDictionary().GetNWordPairs(5);

    MultipleQuestionsStep *step =
            new MultipleQuestionsStep(*this, "Translate the word", words);
    x_AddStepPage(std::unique_ptr<StepPage>(step));

    m_progressStep = new ProgressStep(*this, "Progress");
    x_AddStepPage(std::unique_ptr<StepPage>(m_progressStep));
    connect((QuestionTOMObject*)step, &QuestionTOMObject::finished, [=]() {
        m_progressStep->signalChanged();
    });
}

void AlexandraCoach::reportAnswer(const QString &word, bool isCorrect)
{
    m_profile.GetLanguage().GetDictionary().RecordAnswer(word, isCorrect);
}

double AlexandraCoach::getProgress()
{
    return m_profile.GetLanguage().GetDictionary().GetProgress();
}

void AlexandraCoach::MultipleQuestionsStep::onanswer(QString value)
{
    m_answers.push_back(value);
    QString question = m_questions[m_questionIndex].first;
    QString correctAnswer = m_questions[m_questionIndex].second;
    if (value == correctAnswer) {
        ++m_correct;
        m_owner.reportAnswer(question, true);
    }
    else {
        ++m_mistakes;
        m_owner.reportAnswer(question, false);
    }
    x_MoveNext();
}

void AlexandraCoach::MultipleQuestionsStep::onskip()
{
    m_answers.push_back("");
    ++m_skipped;
    x_MoveNext();
}

void AlexandraCoach::MultipleQuestionsStep::x_MoveNext()
{
    ++m_questionIndex;
    emit invalidated();
    if (m_questionIndex < m_questions.size())
        Update("Translate the word", m_questions[m_questionIndex].first);
    else {
        Update("Translate the word", "Resume");
        emit finished();
    }
}
